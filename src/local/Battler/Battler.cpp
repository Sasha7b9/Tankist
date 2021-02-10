#include "stdafx.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battler)
#ifdef WIN32
#pragma warning(pop)
#endif

Battler::Battler(Context* context)
    : Application(context),
    useMouseMode_(MM_ABSOLUTE)
{
    // Register factory and attributes for the Vehicle component so it can be created via CreateComponent, and loaded / saved
    VehicleLogic::RegisterObject(context);
}


void Battler::Setup()
{
    // Modify engine startup parameters
    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_LOG_NAME] = GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_HEADLESS] = false;
    engineParameters_[EP_SOUND] = false;

    // Construct a search path to find the resource prefix with two entries:
    // The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary when it is still in build tree
    // The second and third entries are possible relative paths from the installed program/bin directory to the asset directory -- these entries are for binary when it is in the Urho3D SDK installation location
    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif
}


void Battler::Start()
{
    TheScene = new Scene(context_);

    TheCache = GetSubsystem<ResourceCache>();
    TheUI = GetSubsystem<UI>();
    TheGraphics = GetSubsystem<Graphics>();
    TheInput = GetSubsystem<Input>();
    TheRenderer = GetSubsystem<Renderer>();
    TheConsole = GetSubsystem<Console>();
    TheFileSystem = GetSubsystem<FileSystem>();

    XMLFile *xmlFile = TheCache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Create console
    TheConsole = engine_->CreateConsole();
    TheConsole->SetDefaultStyle(xmlFile);
    TheConsole->GetBackground()->SetOpacity(0.8f);

    // Create debug HUD.
    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);

    TheMainCamera = new MainCamera(context_);

    logo = new Logo(context_);

    // Set custom window Title & Icon
    SetWindowTitleAndIcon();
    // Create console and debug HUD
    CreateConsoleAndDebugHud();
    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));
    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(Battler, HandleKeyUp));
    // Subscribe scene update event
    SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(Battler, HandleSceneUpdate));
    // Create static scene content
    CreateScene();

    vehicle = new Vehicle(context_);

    Instructions::Create();

    // Subscribe to necessary events
    SubscribeToEvents();
    // Set the mouse mode to use in the sample
    InitMouseMode(MM_RELATIVE);
}


void Battler::Stop()
{
    engine_->DumpResources(true);

    delete vehicle;

    delete logo;

    delete TheMainCamera;

    delete TheScene;
}


void Battler::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/UrhoIcon.png");
    TheGraphics->SetWindowIcon(icon);
    TheGraphics->SetWindowTitle("Urho3D Sample");
}


void Battler::CreateConsoleAndDebugHud()
{
}


void Battler::InitMouseMode(MouseMode mode)
{
    useMouseMode_ = mode;

    if (GetPlatform() != "Web")
    {
        if (useMouseMode_ == MM_FREE)
            TheInput->SetMouseVisible(true);

        if (useMouseMode_ != MM_ABSOLUTE)
        {
            TheInput->SetMouseMode(useMouseMode_);
            if (TheConsole && TheConsole->IsVisible())
                TheInput->SetMouseMode(MM_ABSOLUTE, true);
        }
    }
    else
    {
        TheInput->SetMouseVisible(true);
        SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(Battler, HandleMouseModeRequest));
        SubscribeToEvent(E_MOUSEMODECHANGED, URHO3D_HANDLER(Battler, HandleMouseModeChange));
    }
}


void Battler::CreateScene()
{
    // Create scene subsystem components
    TheScene->CreateComponent<Octree>();
    TheScene->CreateComponent<PhysicsWorld>();
    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load

    // Create static scene content. First create a zone for ambient lighting and fog control
    Node* zoneNode = TheScene->CreateChild("Zone");
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(300.0f);
    zone->SetFogEnd(500.0f);
    zone->SetBoundingBox(BoundingBox(-2000.0f, 2000.0f));
    // Create a directional light with cascaded shadow mapping
    Node* lightNode = TheScene->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);
    // Create heightmap terrain with collision
    Node* terrainNode = TheScene->CreateChild("Terrain");
    terrainNode->SetPosition(Vector3::ZERO);
    auto* terrain = terrainNode->CreateComponent<Terrain>();
    terrain->SetPatchSize(64);
    terrain->SetSpacing(Vector3(3.0f, 0.1f, 3.0f)); // Spacing between vertices and vertical resolution of the height map
    terrain->SetSmoothing(true);
    terrain->SetHeightMap(TheCache->GetResource<Image>("Textures/HeightMap.png"));
    terrain->SetMaterial(TheCache->GetResource<Material>("Materials/Terrain.xml"));
    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain->SetOccluder(true);
    auto* body = terrainNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(2); // Use layer bitmask 2 for static geometry
    auto* shape =
        terrainNode->CreateComponent<CollisionShape>();
    shape->SetTerrain();
    // Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    const unsigned NUM_MUSHROOMS = 1000;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node* objectNode = TheScene->CreateChild("Mushroom");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y_ = terrain->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);
        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain->GetNormal(position)));
        objectNode->SetScale(3.0f);
        auto* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(TheCache->GetResource<Model>("Models/Mushroom.mdl"));
        object->SetMaterial(TheCache->GetResource<Material>("Materials/Mushroom.xml"));
        object->SetCastShadows(true);
        auto* b = objectNode->CreateComponent<RigidBody>();
        b->SetCollisionLayer(2);
        auto* s = objectNode->CreateComponent<CollisionShape>();
        s->SetTriangleMesh(object->GetModel(), 0);
    }
}


void Battler::SubscribeToEvents()
{
    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent(E_UPDATE,
                     URHO3D_HANDLER(Battler, HandleUpdate));
    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE,
                     URHO3D_HANDLER(Battler,
                                    HandlePostUpdate));
    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Battler::HandleUpdate(StringHash , VariantMap& )
{
    if (vehicle)
    {
        vehicle->Update();
    }
}

void Battler::HandlePostUpdate(StringHash , VariantMap& )
{
    if (!vehicle)
    {
        return;
    }

    TheMainCamera->SetOnNode(vehicle->logic->GetNode(), vehicle->logic->controls_.yaw_, vehicle->logic->controls_.pitch_);
}


void Battler::HandleKeyUp(StringHash /*eventType*/, VariantMap &eventData)
{
    using namespace KeyUp;

    int key = eventData[P_KEY].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESCAPE)
    {
        if (TheConsole->IsVisible())
            TheConsole->SetVisible(false);
        else
        {
            if (GetPlatform() == "Web")
            {
                TheInput->SetMouseVisible(true);
                if (useMouseMode_ != MM_ABSOLUTE)
                    TheInput->SetMouseMode(MM_FREE);
            }
            else
                engine_->Exit();
        }
    }
}

void Battler::HandleKeyDown(StringHash /*eventType*/, VariantMap &eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    // Toggle console with F1
    if (key == KEY_F1)
        TheConsole->Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        TheDebugHud->ToggleAll();

    // Common rendering quality controls, only when UI has no focused element
    else if (!TheUI->GetFocusElement())
    {
        // Texture quality
        if (key == '1')
        {
            auto quality = (unsigned)TheRenderer->GetTextureQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            TheRenderer->SetTextureQuality((MaterialQuality)quality);
        }

        // Material quality
        else if (key == '2')
        {
            auto quality = (unsigned)TheRenderer->GetMaterialQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            TheRenderer->SetMaterialQuality((MaterialQuality)quality);
        }

        // Specular lighting
        else if (key == '3')
            TheRenderer->SetSpecularLighting(!TheRenderer->GetSpecularLighting());

        // Shadow rendering
        else if (key == '4')
            TheRenderer->SetDrawShadows(!TheRenderer->GetDrawShadows());

        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = TheRenderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            TheRenderer->SetShadowMapSize(shadowMapSize);
        }

        // Shadow depth and filtering quality
        else if (key == '6')
        {
            ShadowQuality quality = TheRenderer->GetShadowQuality();
            quality = (ShadowQuality)(quality + 1);
            if (quality > SHADOWQUALITY_BLUR_VSM)
                quality = SHADOWQUALITY_SIMPLE_16BIT;
            TheRenderer->SetShadowQuality(quality);
        }

        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = TheRenderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            TheRenderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }

        // Instancing
        else if (key == '8')
            TheRenderer->SetDynamicInstancing(!TheRenderer->GetDynamicInstancing());

        // Take screenshot
        else if (key == '9')
        {
            Image screenshot(context_);
            TheGraphics->TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(TheFileSystem->GetProgramDir() + "Data/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
    }
}


// If the user clicks the canvas, attempt to switch to relative mouse mode on web platform
void Battler::HandleMouseModeRequest(StringHash /*eventType*/, VariantMap &)
{
    if (TheConsole && TheConsole->IsVisible())
        return;
    if (useMouseMode_ == MM_ABSOLUTE)
        TheInput->SetMouseVisible(false);
    else if (useMouseMode_ == MM_FREE)
        TheInput->SetMouseVisible(true);
    TheInput->SetMouseMode(useMouseMode_);
}


void Battler::HandleMouseModeChange(StringHash /*eventType*/, VariantMap &eventData)
{
    bool mouseLocked = eventData[MouseModeChanged::P_MOUSELOCKED].GetBool();
    TheInput->SetMouseVisible(!mouseLocked);
}



void Battler::HandleSceneUpdate(StringHash /*eventType*/, VariantMap &)
{
}
