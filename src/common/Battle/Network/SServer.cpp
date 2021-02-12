#include "stdafx.h"


SServer::SServer(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(SServer, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(SServer, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(SServer, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(SServer, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(SServer, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(SServer, HandleCliendDisconnected));
}


bool SServer::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}


void SServer::HandleMessage(StringHash, VariantMap &eventData)
{
    using namespace NetworkMessage;

    int id = eventData[P_MESSAGEID].GetInt();

    TConnection connection((Connection *)eventData[P_CONNECTION].GetPtr());

    if (id == MSG_TEXTSTRING)
    {
        const PODVector<uint8> &data = eventData[P_DATA].GetBuffer();

        MemoryBuffer msg(data);
        String text = msg.ReadString();
    }
    else if (id == MSG_SCENE_REQUEST_FOR_BUILD)
    {
        connection.SendMessage(MSG_SCENE_BUILD, true, 
            DataNetwork({ 10.0f, 10.0f, 10.0f }));              // Передаём координаты вновь созданной сущности игрока
    }
}


void SServer::HandleServerConnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void SServer::HandleServerDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void SServer::HandleClientConnected(StringHash, VariantMap &eventData)
{
//    LOG_FUNC_ENTER();

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void SServer::HandleCliendDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();

    TheBattle->Exit();
}


void SServer::HandleConnectFailed(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}
