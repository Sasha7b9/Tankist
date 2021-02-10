#include "stdafx.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Server, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleConnectionStatus));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Server, HandleConnectionStatus));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Server, HandleConnectionStatus));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(Server, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(Server, HandleCliendDisconnected));
}


bool Server::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}


void Server::HandleMessage(StringHash, VariantMap &)
{

}


void Server::HandleConnectionStatus(StringHash, VariantMap &)
{

}


void Server::HandleClientConnected(StringHash, VariantMap &eventData)
{
    URHO3D_LOGINFO("New client connected");

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void Server::HandleCliendDisconnected(StringHash, VariantMap &)
{

}
