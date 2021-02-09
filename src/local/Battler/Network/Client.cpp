/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */

#include <stdafx.h>
#include "Client.h"
#include "Network/NetworkEvents.h"



Client::Client(Context *context) : Object(context)
{
    TheNetwork->RegisterRemoteEvent(E_CLIENTOBJECTID);
    SubscribeToEvent(E_CLIENTOBJECTID, URHO3D_HANDLER(Client, HandleClientObjectID));
    TheNetwork->RegisterRemoteEvent(E_STRING_MESSAGE);
    SubscribeToEvent(E_STRING_MESSAGE, URHO3D_HANDLER(Client, HandleStringMessage));

    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Client, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Client, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(Client, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(Client, HandleClientObjectID));
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(Client, HandleNetworkMessage));
}


Client::~Client()
{
    Disconnect();
}


bool Client::ConnectToServer()
{
    towerID = 0;

    return GetSubsystem<Network>()->Connect(TheIPAddress, TheNumPort, TheScene);
}


void Client::Disconnect()
{
    Connection *serverConnnection = TheNetwork->GetServerConnection();
    if (serverConnnection)
    {
        serverConnnection->Disconnect();
        TheScene->Clear(true, false);
        towerID = 0;
    }
}


void Client::HandleClientObjectID(StringHash, VariantMap &eventData)
{
    towerID = eventData[P_ID_TOWER].GetUInt();
    trunkID = eventData[P_ID_TRUNK].GetUInt();
    caseID = eventData[P_ID_CASE].GetUInt();
}


void Client::HandleStringMessage(StringHash, VariantMap& eventData)
{
    String var = eventData[P_STRING_VAR].GetString();
    String value = eventData[P_STRING_VALUE].GetString();

    TheGameGUI->SetVar(var, value);
}


bool Client::AttachCameraToNode()
{
    return TheCamera->SetCameraMode(ModeCommander, TheScene->GetNode(towerID));
}


void Client::HandleServerConnected(StringHash, VariantMap &)
{
    serverIsConnected = true;
}


void Client::HandleServerDisconnected(StringHash, VariantMap &)
{
    URHO3D_LOGINFOF("%s", __FUNCTION__);
}


void Client::HandleConnectFailed(StringHash, VariantMap &)
{
    URHO3D_LOGINFOF("%s", __FUNCTION__);
    float timeStart = TheTime->GetElapsedTime();
    ConnectToServer();
    static int count = 0;
    URHO3D_LOGERRORF("Failed connection %d, time %f ms", count++, (TheTime->GetElapsedTime() - timeStart) * 1000.0f);
}


void Client::HandleNetworkMessage(StringHash, VariantMap &eventData)
{
    using namespace NetworkMessage;

    int msgID = eventData[P_MESSAGEID].GetInt();

    const PODVector<uint8> &data = eventData[P_DATA].GetBuffer();
    MemoryBuffer msg(data);

    if(msgID == MSG_PING)
    {
        TheTankist->SetPing(TheTime->GetElapsedTime() - timePing);
    }
    else if(msgID == MSG_LOAD_CPU)
    {
        float loadCPU = msg.ReadFloat();
        TheTankist->SetLoadCPU(loadCPU);
    }
    else if(msgID == MSG_NUM_CLIENTS)
    {
        int numClients = msg.ReadInt();
        TheTankist->SetNumClients(numClients);
    }
    else if(msgID == MSG_SERVER_SPEED)
    {
        float speedIn = msg.ReadFloat();
        float speedOut = msg.ReadFloat();
        TheTankist->SetBytesInPerSecServer(speedIn);
        TheTankist->SetBytesOutPerSecServer(speedOut);
    }
}


/*
void Client::TranslateChatMessage(const String &message)
{
    VectorBuffer buffer;
    buffer.WriteString(message);
    TheNetwork->GetServerConnection()->SendMessage(MSG_CHAT, true, true, buffer);
}
*/


void Client::RequestSystemInformation()
{
    Connection *connection = TheNetwork->GetServerConnection();

    if(connection)
    {
        VectorBuffer buffer;
        connection->SendMessage(MSG_PING, true, false, buffer);
        timePing = TheTime->GetElapsedTime();
        connection->SendMessage(MSG_LOAD_CPU, true, false, buffer);
        connection->SendMessage(MSG_NUM_CLIENTS, true, false, buffer);
        connection->SendMessage(MSG_SERVER_SPEED, true, false, buffer);


        TheTankist->SetBytesInPerSec(connection->GetBytesInPerSec() + TheCounters->GetClientIn());
        TheTankist->SetBytesOutPerSec(connection->GetBytesOutPerSec() + TheCounters->GetClientOut());
    }
}


void Client::MessageControl(Control control, TypeControl type)
{
    VectorBuffer buffer;
    buffer.WriteInt(control);
    buffer.WriteInt(type);
    TheNetwork->GetServerConnection()->SendMessage(MSG_CONTROL, true, false, buffer);
}
