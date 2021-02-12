#include "stdafx.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Server, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Server, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Server, HandleConnectFailed));
}


void Server::SendTextMessage(const String &message, bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        VectorBuffer msg;
        msg.WriteString(message);

        connection->SendMessage(MSG_TEXTSTRING, reliable, reliable, msg);
    }
}


void Server::SendMessage(int id, bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, nullptr, 0);
    }
}


void Server::SendMessage(int id, bool reliable, const DataNetwork &data)
{

}


//void Server::SendMessage(int id, const VectorBuffer &data, bool reliable)
//{
//    Connection *connection = TheNetwork->GetServerConnection();
//
//    if (connection)
//    {
//        connection->SendMessage(id, reliable, reliable, data);
//    }
//}


void Server::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void Server::HandleMessage(StringHash, VariantMap &eventData)
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


bool Server::IsSceneMessage(int id)
{
    return (id >= MSG_SCENE_REQUEST_FOR_BUILD) && (id <= MSG_SCENE_LAST);
}


void Server::HandleServerConnected(StringHash, VariantMap &)
{
    TheServer->SendMessage(MSG_SCENE_REQUEST_FOR_BUILD, true);
}


void Server::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void Server::HandleConnectFailed(StringHash, VariantMap &)
{
}
