#include "stdafx.h"


void Battler::HandleUpdate(StringHash, VariantMap &)
{
    TheServer->SendMessage(MSG_TEXTSTRING, true, { "Update" });

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
