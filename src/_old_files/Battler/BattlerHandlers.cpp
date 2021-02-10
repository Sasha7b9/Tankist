/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "Battler.h"
#include "globals.h"
#include "defines.h"
#include "Objects/Vehicle.h"



#define SEND_CONTROL(k, ctrl)                  if(key == k && !repeat) { TheClient->MessageControl(ctrl, CTRL_ON); }
#define SEND_CONTROL_MODECAMERA(k, mode, ctrl) if(key == k && mode)    { TheClient->MessageControl(ctrl, CTRL_ON); }



void Battler::HandleKeyDown(StringHash, VariantMap& eventData)
    {
#ifdef WIN32
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();
    bool repeat = eventData[P_REPEAT].GetBool();

    if(!TheUI->GetFocusElement())
    {
        bool modeShooter = TheCamera->GetMode() == ModeShooter;
        bool modeCommander = TheCamera->GetMode() == ModeCommander;

        SEND_CONTROL(KEY_W,         CTRL_FORWARD)
        else SEND_CONTROL(KEY_S,    CTRL_BACK)
        else SEND_CONTROL(KEY_A,    CTRL_LEFT)
        else SEND_CONTROL(KEY_D,    CTRL_RIGHT)
        else SEND_CONTROL_MODECAMERA(KEY_KP_2, modeShooter,     CTRL_TRUNK_DOWN)
        else SEND_CONTROL_MODECAMERA(KEY_KP_2, modeCommander,   CTRL_TRUNK_DOWN_FAST)
        else SEND_CONTROL_MODECAMERA(KEY_KP_8, modeShooter,     CTRL_TRUNK_UP)
        else SEND_CONTROL_MODECAMERA(KEY_KP_8, modeCommander,   CTRL_TRUNK_UP_FAST)
        else SEND_CONTROL_MODECAMERA(KEY_E,    modeShooter,     CTRL_TOWER_RIGHT)
        else SEND_CONTROL_MODECAMERA(KEY_KP_6, modeShooter,     CTRL_TOWER_RIGHT)
        else SEND_CONTROL_MODECAMERA(KEY_E,    modeCommander,   CTRL_TOWER_RIGHT_FAST)
        else SEND_CONTROL_MODECAMERA(KEY_KP_6, modeCommander,   CTRL_TOWER_RIGHT_FAST)
        else SEND_CONTROL_MODECAMERA(KEY_Q,    modeShooter,     CTRL_TOWER_LEFT)
        else SEND_CONTROL_MODECAMERA(KEY_KP_4, modeShooter,     CTRL_TOWER_LEFT)
        else SEND_CONTROL_MODECAMERA(KEY_Q,    modeCommander,   CTRL_TOWER_LEFT_FAST)
        else SEND_CONTROL_MODECAMERA(KEY_KP_4, modeCommander,   CTRL_TOWER_LEFT_FAST)
    }

    // Close console (if open) or exit when ESC is pressed
    if(key == KEY_ESCAPE)
    {
        if(TheConsole->IsVisible())
        {
            TheConsole->SetVisible(false);
        }
        else
        {
            if(TheGame->GetState() == InProcess)
            {
                TheWindowGameESC->Show();
                TheGame->SetState(State_WindowGameESC);
            }
            else
            {
                TheWindowGameESC->Hide();
                TheGame->SetState(InProcess);
            }
        }
    }
    else if(key == KEY_RETURN)
    {
        if(!TheConsole->IsVisible())
        {
            if(!TheChat->IsActive())
            {
                TheChat->SetActive(true);
            }
            else
            {
                TheChat->PressEnter();
            }
        }
    }

    // Toggle console with F1
    else if(key == KEY_F1)
    {
        TheConsole->Toggle();
    }

    // Toggle debug HUD with F2
    else if(key == KEY_F2)
    {
        if(TheDebugHud->GetMode() == 0 || TheDebugHud->GetMode() == DEBUGHUD_SHOW_MEMORY)
        {
            TheDebugHud->SetMode(DEBUGHUD_SHOW_ALL);
        }
        else
        {
            TheDebugHud->SetMode(DEBUGHUD_SHOW_NONE);
        }
    }
    else if(key == KEY_F3)
    {
        if(TheDebugHud->GetMode() == 0 || TheDebugHud->GetMode() == DEBUGHUD_SHOW_ALL)
        {
            TheDebugHud->SetMode(DEBUGHUD_SHOW_MEMORY);
        }
        else
        {
            TheDebugHud->SetMode(DEBUGHUD_SHOW_NONE);
        }
    }

    else if(key == KEY_KP_ENTER)
    {
        TheAudioCapturer->Pause(false);
    }

    else if(key == KEY_KP_PLUS)
    {
        TheCamera->IncFov();
    }

    else if(key == KEY_KP_MINUS)
    {
        TheCamera->DecFov();
    }

    else if(key == KEY_KP_MULTIPLY)
    {
        TheCamera->DefaultFov();
    }

    else if(key == KEY_SPACE)
    {
        TheCamera->SetCameraMode(ModeShooter, TheScene->GetNode(TheClient->trunkID));
    }

    else if(key == KEY_F9)
    {
        TheCamera->SetCameraMode(ModeCommander, TheScene->GetNode(TheClient->towerID));
    }

    else if(key == KEY_CTRL)
    {
        if(!eventData[P_REPEAT].GetBool())
        {
            TheGame->Shot();
        }
    }

    // Common rendering quality controls, only when UI has no focused element
    else if(!TheUI->GetFocusElement())
    {
        // Texture quality
        if(key == '1')
        {
            uint quality = TheRenderer->GetTextureQuality();
            ++quality;
            if(quality > QUALITY_HIGH)
            {
                quality = QUALITY_LOW;
            }
            TheRenderer->SetTextureQuality((MaterialQuality)quality);
        }

        // Material quality
        else if(key == '2')
        {
            uint quality = TheRenderer->GetMaterialQuality();
            ++quality;
            if(quality > QUALITY_HIGH)
            {
                quality = QUALITY_LOW;
            }
            TheRenderer->SetMaterialQuality((MaterialQuality)quality);
        }

        // Specular lighting
        else if(key == '3')
        {
            TheRenderer->SetSpecularLighting(!TheRenderer->GetSpecularLighting());
        }

        // Shadow rendering
        else if(key == '4')
        {
            TheRenderer->SetDrawShadows(!TheRenderer->GetDrawShadows());
        }

        // Shadow map resolution
        else if(key == '5')
        {
            int shadowMapSize = TheRenderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if(shadowMapSize > 2048)
            {
                shadowMapSize = 512;
            }
            TheRenderer->SetShadowMapSize(shadowMapSize);
        }

        // Shadow depth and filtering quality
        else if(key == '6')
        {
            ShadowQuality quality = TheRenderer->GetShadowQuality();
            quality = (ShadowQuality)(quality + 1);
            if(quality > SHADOWQUALITY_BLUR_VSM)
            {
                quality = SHADOWQUALITY_SIMPLE_16BIT;
            }
            TheRenderer->SetShadowQuality(quality);
        }

        // Occlusion culling
        else if(key == '7')
        {
            bool occlusion = TheRenderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            TheRenderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }

        // Instancing
        else if(key == '8')
        {
            TheRenderer->SetDynamicInstancing(!TheRenderer->GetDynamicInstancing());
        }

        // Take screenshot
        else if(key == '9')
        {
            Image screenshot(context_);
            TheGraphics->TakeScreenShot(screenshot);
            // Here we save in the Data folder with date and time appended
            screenshot.SavePNG(TheFileSystem->GetProgramDir() + "Data/Screenshot_" +
                               Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        else if(key == KEY_F12)
        {
            UIElement *instr = TheUI->GetRoot()->GetChild(INSTRUCTION);
            instr->SetVisible(!instr->IsVisible());
        }
    }
#endif
}

#define SEND_CONTROL_OFF(k, ctrl) if(key == k) { TheClient->MessageControl(ctrl, CTRL_OFF); }
#define SEND_CONTROL_MODECAMERA_OFF(k, mode, ctrl) if(key == k && mode) { TheClient->MessageControl(ctrl, CTRL_OFF); }


void Battler::HandleKeyUp(StringHash, VariantMap& eventData)
{
#ifdef WIN32
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    bool modeShooter = TheCamera->GetMode() == ModeShooter;
    bool modeCommander = TheCamera->GetMode() == ModeCommander;

    SEND_CONTROL_OFF(KEY_A, CTRL_LEFT)
    else SEND_CONTROL_OFF(KEY_D, CTRL_RIGHT)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_2, modeShooter, CTRL_TRUNK_DOWN)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_2, modeCommander, CTRL_TRUNK_DOWN_FAST)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_8, modeShooter, CTRL_TRUNK_UP)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_8, modeCommander, CTRL_TRUNK_UP_FAST)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_E, modeShooter, CTRL_TOWER_RIGHT)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_6, modeShooter, CTRL_TOWER_RIGHT)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_E, modeCommander, CTRL_TOWER_RIGHT_FAST)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_6, modeCommander, CTRL_TOWER_RIGHT_FAST)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_Q, modeShooter, CTRL_TOWER_LEFT)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_4, modeShooter, CTRL_TOWER_LEFT)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_Q, modeCommander, CTRL_TOWER_LEFT_FAST)
    else SEND_CONTROL_MODECAMERA_OFF(KEY_KP_4, modeCommander, CTRL_TOWER_LEFT_FAST)

    if(key == KEY_KP_ENTER)
    {
        TheAudioCapturer->Pause(true);
    }
#endif
}



void Battler::HandlePostUpdate(StringHash, VariantMap &)
{
    TheCounters->Update();

    static float prevTime = 0.0f;

    float curTime = TheTime->GetElapsedTime();

    if((curTime - prevTime) > 1.0f)
    {
        TheClient->RequestSystemInformation();
        prevTime = curTime;
    }

    if(TheTypeApplication == Type_Client)
    {
        UpdateCamera();
    }

    if(exit)
    {
        engine_->Exit();
    }

    if(TheChat)
    {
        TheChat->UpdateChat();
    }
}



void Battler::HandleLanguageChanged(StringHash, VariantMap&)
{
    PODVector<UIElement*> elements;
    TheUIRoot->GetChildren(elements, true);

    for(UIElement *element : elements)
    {
        if(element->GetType() == "Text")
        {
            String name = element->GetName();
            if(!name.Empty() && name != "DDL_Placeholder_Text" && name != "LE_Text" &&
               name != "TextValue"                                                          // This controls for information
               )
            {
                String text = TheLocale->Get(name);
                if(!text.Empty())
                {
                    ((Text*)element)->SetText(text);
                }
            }
        }
    }
}



void Battler::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(TheDebugRenderer && TheScene->GetComponent<PhysicsWorld>())
    {
        TheScene->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);

        PODVector<Node*> nodes;
        TheScene->GetChildren(nodes, true);
        for(Node *node : nodes)
        {
            if(node->GetName() == "damper")
            {
                CollisionShape *shape = node->GetComponent<CollisionShape>();
                if(shape)
                {
                    shape->DrawDebugGeometry(TheDebugRenderer, true);
                }
            }

            if(node->GetName() == "Tank")
            {
                Vehicle *tank = node->GetComponent<Vehicle>();
                if(tank)
                {
                    tank->Logging();
                }
            }
        }
    }
}
