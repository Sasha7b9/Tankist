/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "WindowGameESC.h"



WindowGameESC::WindowGameESC(Context *context) : Object(context)
{
    window = TheUI->LoadLayout(TheCache->GetResource<XMLFile>("UI/Elements/WindowGameESC.xml"));
    TheUIRoot->AddChild(window);

    int posX = TheUIRoot->GetWidth() / 2 - window->GetWidth() / 2;
    int posY = TheUIRoot->GetHeight() / 2 - window->GetHeight() / 2;

    window->SetPosition(posX, posY);

    Hide();

    Button *bExit = (Button*)window->GetChild("bExit", true);
    SubscribeToEvent(bExit, E_RELEASED, URHO3D_HANDLER(WindowGameESC, HandleButtonExit));

    Button *bSettings = (Button*)window->GetChild("bSettings", true);
    SubscribeToEvent(bSettings, E_RELEASED, URHO3D_HANDLER(WindowGameESC, HandleButtonSettings));

    Button *bLanguage = (Button*)window->GetChild("bLanguage", true);
    SubscribeToEvent(bLanguage, E_RELEASED, URHO3D_HANDLER(WindowGameESC, HandleButtonLanguage));

    window->SetOpacity(0.75f);
}


void WindowGameESC::Hide()
{
    window->SetVisible(false);
}


void WindowGameESC::Show()
{
    window->SetVisible(true);
    window->SetBringToFront(true);
    window->SetFocus(true);
    window->BringToFront();
}


void WindowGameESC::HandleButtonExit(StringHash, VariantMap&)
{
    TheTankist->Exit();
}


void WindowGameESC::HandleButtonLanguage(StringHash, VariantMap&)
{
    TheSet->Set(LANGUAGE, TheLocale->GetLanguage() == String("ru") ? 0 : 1);
    TheLocale->SetLanguage(TheSet->Get(LANGUAGE) == 0 ? "en" : "ru");
}


void WindowGameESC::HandleButtonSettings(StringHash, VariantMap&)
{
    Hide();
    TheWindowSettings->Show();
}
