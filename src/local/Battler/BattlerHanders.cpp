/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


void Battler::HandleUpdate(StringHash, VariantMap &)
{
//    MessageTextString("Update").Send(true);

    if (TheVehicle)
    {
        TheVehicle->Update();
    }

    if (TheMainCamera)
    {
        TheMainCamera->Update();
    }
}


void Battler::HandlePostUpdate(StringHash, VariantMap &)
{

}


void Battler::HandleSceneUpdate(StringHash /*eventType*/, VariantMap &)
{
}
