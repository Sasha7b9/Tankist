#include "stdafx.h"


void GMessage::BuildScene::Handle(MemoryBuffer &msg)
{
    TheScene->Create();

    TheVehicle = new Vehicle(TheContext);

    TheVehicle->logic->GetNode()->SetPosition(msg.ReadVector3());

    TheMainCamera = new MainCamera(TheVehicle->logic->GetNode(), TheContext);

}
