// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void Instructions::Create()
{
    // Construct new Text object, set string to display and font to use
    auto *instructionText = TheUI->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys to drive, F to brake, mouse/touch to rotate camera\n"
        "F5 to save scene, F7 to load");
    instructionText->SetFont(TheCache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);
    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, TheUI->GetRoot()->GetHeight() / 4);
}
