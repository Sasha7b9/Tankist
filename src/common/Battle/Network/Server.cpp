#include "stdafx.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Server, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Server, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Server, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(Server, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(Server, HandleCliendDisconnected));
}


bool Server::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}


void Server::HandleMessage(StringHash, VariantMap &eventData)
{
    using namespace NetworkMessage;

    int id = eventData[P_MESSAGEID].GetInt();

    HeadConnection connection((Connection *)eventData[P_CONNECTION].GetPtr());

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


void Server::HandleServerConnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void Server::HandleServerDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void Server::HandleClientConnected(StringHash, VariantMap &eventData)
{
//    LOG_FUNC_ENTER();

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(newConnection);
}


void Server::HandleCliendDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();

    TheBattle->Exit();
}


void Server::HandleConnectFailed(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}
