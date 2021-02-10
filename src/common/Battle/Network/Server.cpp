#include "stdafx.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Server, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Server, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Server, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(Server, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(Server, HandleCliendDisconnected));
}


bool Server::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}


void Server::HandleMessage(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void Server::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void Server::HandleServerDisconnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void Server::HandleClientConnected(StringHash, VariantMap &eventData)
{
    LOG_FUNC_ENTER();

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void Server::HandleCliendDisconnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void Server::HandleConnectFailed(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}
