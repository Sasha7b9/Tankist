/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


void Battle::HandleUpdate(StringHash, VariantMap &)
{

}


void Battle::HandlePostUpdate(StringHash, VariantMap &)
{
    if (TheVehicle)
    {
        TheVehicle->logic->GetState()->Send();
    }
}
