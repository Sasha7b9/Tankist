#include "stdafx.h"


HeadServer::HeadServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(HeadServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(HeadServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(HeadServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(HeadServer, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(HeadServer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(HeadServer, HandleCliendDisconnected));
}


bool HeadServer::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}


void HeadServer::HandleMessage(StringHash, VariantMap &eventData)
{
    LOG_FUNC_ENTER();

    using namespace NetworkMessage;

    if (eventData[P_MESSAGEID].GetInt() == MSG_TEXTSTRING)
    {
        const PODVector<uint8> &data = eventData[P_DATA].GetBuffer();

        MemoryBuffer msg(data);
        String text = msg.ReadString();

        URHO3D_LOGINFOF("Receive message : \"%s\"", text.CString());
    }
}


void HeadServer::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void HeadServer::HandleServerDisconnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void HeadServer::HandleClientConnected(StringHash, VariantMap &eventData)
{
    LOG_FUNC_ENTER();

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void HeadServer::HandleCliendDisconnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();

    TheBattle->Exit();
}


void HeadServer::HandleConnectFailed(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}
