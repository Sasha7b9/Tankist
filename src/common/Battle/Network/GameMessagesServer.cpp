#include "stdafx.h"


void Message::Message::Send(bool)
{

}


void Message::RequestForBuildScene::Handle(const TConnection &connection)
{


    connection.SendMessage(true, BuildScene({ 10.0f, 10.0f, 10.0f }));
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
