#include "stdafx.h"


ClientServer::ClientServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ClientServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ClientServer, HandleConnectFailed));
}


void ClientServer::SendMessage(const String &message)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        VectorBuffer msg;
        msg.WriteString(message);

        connection->SendMessage(MSG_TEXTSTRING, true, true, msg);
    }
}


void ClientServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void ClientServer::HandleMessage(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void ClientServer::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();

    TheScene->Create(this);
}


void ClientServer::HandleServerDisconnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void ClientServer::HandleConnectFailed(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}
