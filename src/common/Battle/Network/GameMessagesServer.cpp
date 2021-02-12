/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


void Message::RequestForBuildScene::Handle(const TConnection &connection)
{
    TheVehicle = new Vehicle(TheContext);

    Vector3 position(10.0f, 10.0f, 10.0f);

    TheVehicle->logic->GetNode()->SetPosition(position);

    connection.SendMessage(true, BuildScene(position));
}


void Message::KeyEvent::Handle(MemoryBuffer &msg)
{
    int key = msg.ReadInt();
    bool press = msg.ReadBool();

    if (TheVehicle)
    {
        TheVehicle->logic->UpdateControls((Key)key, press);
    }
}
