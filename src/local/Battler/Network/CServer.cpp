#include "stdafx.h"


CServer::CServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(CServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(CServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(CServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(CServer, HandleConnectFailed));
}


void GMessage::GameMessage::Send(bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, buffer);
    }
}


void CServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void CServer::HandleMessage(StringHash, VariantMap &eventData)
{
    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();

    GMessage::GameMessage(id).Handle(eventData);
}


void CServer::HandleServerConnected(StringHash, VariantMap &)
{
    GMessage::RequestForBuildScene().Send(true);
}


void CServer::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void CServer::HandleConnectFailed(StringHash, VariantMap &)
{
}
