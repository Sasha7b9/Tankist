/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
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
    TheContext = context_;
    TheCache = GetSubsystem<ResourceCache>();
    TheUI = GetSubsystem<UI>();
    TheGraphics = GetSubsystem<Graphics>();
    TheInput = new Keyboard(context_);
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

    Instructions::Create();

    // Subscribe to necessary events
    SubscribeToEvents();

    TheMouse = new Mouse(context_);

    TheServer = new CServer(context_);

    TheServer->Connect("127.0.0.1", 30000);

    TheBattler = this;
}


void Battler::Stop()
{
    engine_->DumpResources(true);

//    engine_->DumpMemory();

    delete TheInput;
    delete TheServer;
    delete TheMouse;
    delete TheVehicle;
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
    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battler, HandleUpdate));

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battler, HandlePostUpdate));
}


void Battler::Exit()
{
    engine_->Exit();
}
