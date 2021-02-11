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

    TheScene = new GameScene(context_);

    vehicle = new Vehicle(context_);

    TheMainCamera = new MainCamera(vehicle->logic->GetNode(), context_);

    Instructions::Create();

    // Subscribe to necessary events
    SubscribeToEvents();

    TheMouse = new MouseT(context_);

    TheServer = new ClientServer(context_);

    TheServer->Connect("127.0.0.1", 30000);

    TheBattler = this;

    TheScene->Create(TheServer);
}


void Battler::Stop()
{
    engine_->DumpResources(true);

//    engine_->DumpMemory();

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


void Battler::Exit()
{
    engine_->Exit();
}
