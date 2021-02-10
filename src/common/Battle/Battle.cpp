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

    TheServer = new Server();

    TheServer->Start(SERVER_PORT);
}


void Battle::Stop()
{

}


void Battle::SubscribeToEvents()
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Battle, HandleNetworkMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Battle, HandleConnectionStatus));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Battle, HandleConnectionStatus));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Battle, HandleConnectionStatus));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(Battle, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(Battle, HandleCliendDisconnected));
}


void Battle::HandleNetworkMessage(StringHash, VariantMap &)
{

}


void Battle::HandleConnectionStatus(StringHash, VariantMap &)
{

}


void Battle::HandleClientConnected(StringHash, VariantMap &eventData)
{
    URHO3D_LOGINFO("New client connected");

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void Battle::HandleCliendDisconnected(StringHash, VariantMap &)
{

}
