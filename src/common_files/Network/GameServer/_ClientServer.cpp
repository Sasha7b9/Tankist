#include "stdafx.h"


ClientServer::ClientServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ClientServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ClientServer, HandleConnectFailed));
}


void ClientServer::SendTextMessage(const String &message)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        VectorBuffer msg;
        msg.WriteString(message);

        connection->SendMessage(MSG_TEXTSTRING, true, true, msg);
    }
}


void ClientServer::SendMessage(int id)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, true, true, nullptr, 0);
    }
}


void ClientServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void ClientServer::HandleMessage(StringHash, VariantMap &eventData)
{
    LOG_FUNC_ENTER();

    using namespace NetworkMessage;

    int id = eventData[P_MESSAGEID].GetInt();

    if (id == MSG_SCENE_REQUEST_FOR_BUILD)
    {
        SendEvent(E_SCENEMESSAGE);
    }
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
