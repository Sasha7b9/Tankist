/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "Game.h"
#include "globals.h"
#include "defines.h"
#include "Network/NetworkEvents.h"



Game::Game(Context *context) : Object(context)
{

}


void Game::Start()
{
    SubscribeToEvents();
}


void Game::SubscribeToEvents()
{
    SubscribeToEvent(E_PHYSICSPRESTEP, URHO3D_HANDLER(Game, HandlePhysicsPreStep));
}


void Game::HandlePhysicsPreStep(StringHash, VariantMap &)
{
    // Client
    if(TheTypeApplication == Type_Client)
    {
        Connection *serverConnection = TheNetwork->GetServerConnection();

        if(serverConnection)
        {
        }
    }
    // Server
    else
    {
        if(TheNetwork->IsServerRunning())
        {
            const Vector<SharedPtr<Connection>> &connections = TheNetwork->GetClientConnections();

            for(uint i = 0; i < connections.Size(); ++i)
            {
            }
        }
    }
}


void Game::ClientDisconnected(Connection *connection)
{
    Vehicle *object = objects[connection];
    if(object)
    {
        object->Delete();
    }
    objects.Erase(connection);

#ifdef WIN32

    if (objects.Size() == 0)
    {
        TheTankist->Exit();
    }

#endif
}


Vehicle* Game::ClientConnected(Connection *connection)
{
    Vehicle *tank = CreateTank();
    objects[connection] = tank;
    return tank;
}


Vehicle* Game::CreateTank()
{
    Node* tankNode = TheScene->CreateChild("Tank");
    tankNode->SetPosition(Vector3(0.0f, 110.0f, 0.0f));

    Vehicle *tank = tankNode->CreateComponent<Vehicle>();
    tank->Init();

    return tank;
}


void Game::Shot()
{
    VariantMap eventData;
    eventData[P_ID_TRUNK] = TheClient->trunkID;
    TheNetwork->GetServerConnection()->SendRemoteEvent(E_SHOOT, true, eventData);
}
