#include "stdafx.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battler)
#ifdef WIN32
#pragma warning(pop)
#endif

Battler::Battler(Context* context)
    : Application(context)
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
    TheNetwork = GetSubsystem<Network>();

    XMLFile *xmlFile = TheCache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    // Create console
    TheConsole = engine_->CreateConsole();
    TheConsole->SetDefaultStyle(xmlFile);
    TheConsole->GetBackground()->SetOpacity(0.8f);

    // Create debug HUD.
    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);

    logo = new Logo(context_);

    // Set custom window Title & Icon
    SetWindowTitleAndIcon();

    // Create static scene content
    CreateScene();

    vehicle = new Vehicle(context_);

    TheMainCamera = new MainCamera(vehicle->logic->GetNode(), context_);

    Instructions::Create();

    // Subscribe to necessary events
    SubscribeToEvents();

    TheMouse = new MouseT(context_);

    TheServer = new Server(context_);

    TheServer->Connect("127.0.0.1", 30000);
}


void Battler::Stop()
{
    engine_->DumpResources(true);

    engine_->DumpMemory();

    delete TheServer;

    delete TheMouse;

    delete vehicle;

    delete logo;

    delete TheMainCamera;

    delete TheScene;
}


void Battler::SetWindowTitleAndIcon()
{
    Image *icon = TheCache->GetResource<Image>("Textures/UrhoIcon.png");
    TheGraphics->SetWindowIcon(icon);
    TheGraphics->SetWindowTitle(GetTypeName());
}


void Battler::CreateScene()
{
    // Create scene subsystem components
    TheScene->CreateComponent<Octree>();
    TheScene->CreateComponent<PhysicsWorld>();

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
    auto* shape = terrainNode->CreateComponent<CollisionShape>();
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
    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));

    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(Battler, HandleKeyUp));

    // Subscribe scene update event
    SubscribeToEvent(E_SCENEUPDATE, URHO3D_HANDLER(Battler, HandleSceneUpdate));

    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battler, HandleUpdate));

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battler, HandlePostUpdate));

    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}
