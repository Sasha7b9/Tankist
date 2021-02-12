#include "stdafx.h"


CServer::CServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(CServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(CServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(CServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(CServer, HandleConnectFailed));
}


void CServer::SendMessage(bool reliable, const Message &message)
{
    TConnection(TheNetwork->GetServerConnection()).SendMessage(message.id, reliable, message.buffer);
}

void CServer::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void CServer::HandleMessage(StringHash, VariantMap &eventData)
{
    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();

    Message(id).Handle(eventData);
}


bool CServer::IsSceneMessage(int id)
{
    return (id >= MSG_REQUEST_FOR_BUILD_SCENE) && (id <= MSG_SCENE_LAST);
}


void CServer::HandleServerConnected(StringHash, VariantMap &)
{
    TheServer->SendMessage(true, MessageRequestForBuildScene());
}


void CServer::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void CServer::HandleConnectFailed(StringHash, VariantMap &)
{
}
