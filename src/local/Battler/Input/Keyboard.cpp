// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Keyboard::Keyboard(Context *context) : IInput(context)
{
    input = GetSubsystem<Input>();

    SubscribeToEvents();
}


Keyboard::~Keyboard()
{
}


void Keyboard::SubscribeToEvents()
{
    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Keyboard, HandleKeyDown));

    // Subscribe key up event
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(Keyboard, HandleKeyUp));
}


void Keyboard::HandleKeyDown(StringHash /*eventType*/, VariantMap &eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    if (TheVehicle)
    {
        TheVehicle->logic->UpdateControls((Key)key, true);
    }

    // Toggle console with F1
    if (key == KEY_F1)
        TheConsole->Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
        TheDebugHud->ToggleAll();

    // Common rendering quality controls, only when UI has no focused element
    else if (!TheUI->GetFocusElement())
    {
        // Texture quality
        if (key == '1')
        {
            auto quality = (unsigned)TheRenderer->GetTextureQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            TheRenderer->SetTextureQuality((MaterialQuality)quality);
        }

        // Material quality
        else if (key == '2')
        {
            auto quality = (unsigned)TheRenderer->GetMaterialQuality();
            ++quality;
            if (quality > QUALITY_HIGH)
                quality = QUALITY_LOW;
            TheRenderer->SetMaterialQuality((MaterialQuality)quality);
        }

        // Specular lighting
        else if (key == '3')
            TheRenderer->SetSpecularLighting(!TheRenderer->GetSpecularLighting());

        // Shadow rendering
        else if (key == '4')
            TheRenderer->SetDrawShadows(!TheRenderer->GetDrawShadows());

        // Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = TheRenderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if (shadowMapSize > 2048)
                shadowMapSize = 512;
            TheRenderer->SetShadowMapSize(shadowMapSize);
        }

        // Shadow depth and filtering quality
        else if (key == '6')
        {
            ShadowQuality quality = TheRenderer->GetShadowQuality();
            quality = (ShadowQuality)(quality + 1);
            if (quality > SHADOWQUALITY_BLUR_VSM)
                quality = SHADOWQUALITY_SIMPLE_16BIT;
            TheRenderer->SetShadowQuality(quality);
        }

        // Occlusion culling
        else if (key == '7')
        {
            bool occlusion = TheRenderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            TheRenderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }

        // Instancing
        else if (key == '8')
            TheRenderer->SetDynamicInstancing(!TheRenderer->GetDynamicInstancing());

        // Take screenshot
        else if (key == '9')
        {
            Image screenshot(context_);
            TheGraphics->TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(TheFileSystem->GetProgramDir() + "Data/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
    }
}


void Keyboard::HandleKeyUp(StringHash /*eventType*/, VariantMap &eventData)
{
    using namespace KeyUp;

    int key = eventData[P_KEY].GetInt();

    if (TheVehicle)
    {
        TheVehicle->logic->UpdateControls((Key)key, false);
    }

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESCAPE)
    {
        if (TheConsole->IsVisible())
        {
            TheConsole->SetVisible(false);
        }
        else
        {
            if (GetPlatform() == "Web")
            {
                TheInput->input->SetMouseVisible(true);
                if (TheMouse->mode != MM_ABSOLUTE)
                {
                    TheInput->input->SetMouseMode(MM_FREE);
                }
            }
            else
                TheBattler->Exit();
        }
    }
}


bool Keyboard::GetKeyDown(Key key) const
{
    return input->GetKeyDown(key);
}


bool Keyboard::GetKeyPress(Key key) const
{
    return input->GetKeyPress(key);
}
