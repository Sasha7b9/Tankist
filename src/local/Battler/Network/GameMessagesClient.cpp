#include "stdafx.h"


void Message::Message::Send(bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, buffer);
    }
}


void Message::BuildScene::Handle(MemoryBuffer &msg)
{
    TheScene->Create();

    TheVehicle = new Vehicle(TheContext);

    TheVehicle->logic->GetNode()->SetPosition(msg.ReadVector3());

    TheMainCamera = new MainCamera(TheVehicle->logic->GetNode(), TheContext);

}
