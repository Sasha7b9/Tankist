#include "stdafx.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Server, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Server, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Server, HandleConnectFailed));
}


void Server::SendMessage(const String &message)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        VectorBuffer msg;
        msg.WriteString(message);

        connection->SendMessage(MSG_USER, true, true, msg);
    }
}


void Server::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
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


void Server::HandleConnectFailed(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}
