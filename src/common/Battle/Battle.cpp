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
    TheNetwork = GetSubsystem<Network>();

    TheServer = new HeadServer(context_);

    TheServer->Start(SERVER_PORT);

    TheBattle = this;
}


void Battle::Stop()
{
    engine_->DumpResources(true);

    delete TheServer;

//    engine_->DumpMemory();
}


void Battle::Exit()
{
    engine_->Exit();
}