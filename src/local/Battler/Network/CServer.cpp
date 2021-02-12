#include "stdafx.h"


CServer::CServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(CServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(CServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(CServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(CServer, HandleConnectFailed));
}


//void CServer::SendTextMessage(const String &message, bool reliable)
//{
//    Connection *connection = TheNetwork->GetServerConnection();
//
//    if (connection)
//    {
//        VectorBuffer msg;
//        msg.WriteString(message);
//
//        connection->SendMessage(MSG_TEXTSTRING, reliable, reliable, msg);
//    }
//}


void CServer::SendMessage(int id, bool reliable, const DataNetwork &data)
{
    TConnection(TheNetwork->GetServerConnection()).SendMessage(id, reliable, data);
}


void CServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void CServer::HandleMessage(StringHash, VariantMap &eventData)
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


bool CServer::IsSceneMessage(int id)
{
    return (id >= MSG_SCENE_REQUEST_FOR_BUILD) && (id <= MSG_SCENE_LAST);
}


void CServer::HandleServerConnected(StringHash, VariantMap &)
{
    TheServer->SendMessage(MSG_SCENE_REQUEST_FOR_BUILD, true, DataNetwork());
}


void CServer::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void CServer::HandleConnectFailed(StringHash, VariantMap &)
{
}
