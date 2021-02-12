#include "stdafx.h"


ClientServer::ClientServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ClientServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ClientServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ClientServer, HandleConnectFailed));
}


void ClientServer::SendTextMessage(const String &message, bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        VectorBuffer msg;
        msg.WriteString(message);

        connection->SendMessage(MSG_TEXTSTRING, reliable, reliable, msg);
    }
}


void ClientServer::SendMessage(int id, bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, nullptr, 0);
    }
}


void ClientServer::SendMessage(int id, const VectorBuffer &data, bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, data);
    }
}


void ClientServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void ClientServer::HandleMessage(StringHash, VariantMap &eventData)
{
    using namespace NetworkMessage;;

    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();

    MemoryBuffer msg(eventData[P_DATA].GetBuffer());

    if (id == MSG_SCENE_BUILD)
    {
        TheScene->Create();

        TheVehicle = new Vehicle(context_);

        TheVehicle->logic->GetNode()->SetPosition(msg.ReadVector3());

        TheMainCamera = new MainCamera(TheVehicle->logic->GetNode(), context_);
        //TheMainCamera = new MainCamera(nullptr, context_);
    }
}


bool ClientServer::IsSceneMessage(int id)
{
    return (id >= MSG_SCENE_REQUEST_FOR_BUILD) && (id <= MSG_SCENE_LAST);
}


void ClientServer::HandleServerConnected(StringHash, VariantMap &)
{
    TheServer->SendMessage(MSG_SCENE_REQUEST_FOR_BUILD, true);
}


void ClientServer::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void ClientServer::HandleConnectFailed(StringHash, VariantMap &)
{
}
