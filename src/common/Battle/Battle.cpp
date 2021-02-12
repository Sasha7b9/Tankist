/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battle)
#ifdef WIN32
#pragma warning(pop)
#endif


Battle::Battle(Context *context) : Application(context)
{
    VehicleLogic::RegisterObject(context);
}


void Battle::Setup()
{
    engineParameters_[EP_LOG_NAME] = GetTypeName() + ".log";
    engineParameters_[EP_HEADLESS] = true;

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
#ifdef DEBUG
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/debug";
#else
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ";../../../../../../out/release";
#endif
}


void Battle::Start()
{
    TheContext = context_;
    TheCache = GetSubsystem<ResourceCache>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheNetwork = GetSubsystem<Network>();
    TheServer = new SServer(context_);
    TheServer->Start(SERVER_PORT);
    TheBattle = this;

    TheScene = new GameScene(context_);

    TheScene->Create();

    SubscribeToEvents();
}


void Battle::Stop()
{
    engine_->DumpResources(true);

    delete TheVehicle;

    delete TheScene;

    delete TheServer;

//    engine_->DumpMemory();
}


void Battle::Exit()
{
    engine_->Exit();
}


void Battle::SubscribeToEvents()
{
    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Battle, HandleUpdate));

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battle, HandlePostUpdate));
}
