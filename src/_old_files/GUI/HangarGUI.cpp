#include <stdafx.h>
#include "HangarGUI.h"



HangarGUI::HangarGUI() : Window(""),
    btnLanguageObserver(this, &HangarGUI::HandleButtonLanguage),
    btnHelpObserver(this, &HangarGUI::HandleButtonHelp),
    btnSettingsObserver(this, &HangarGUI::HandleButtonSettings),
    btnGoObserver(this, &HangarGUI::HandleButtonGo)
{
    TheInterfaceMgr->SetDefaultFont("font/Gui");

    SetWidgetSize(TheInterfaceMgr->GetDesktopSize());

    CreateButtons();

    TheInterfaceMgr->ResetDefaultFont();

    Show();
}


void HangarGUI::CreateButtons()
{
    static Vector2D size(150, 50);

    PushButtonWidget *btnLanguage = new PushButtonWidget(size, "Language");
    if (btnLanguage)
    {
        btnLanguage->SetObserver(&btnLanguageObserver);
        widgets.AddElement(btnLanguage);
    }

    PushButtonWidget *btnHelp = new PushButtonWidget(size, "Help");
    widgets.AddElement(btnHelp);
    btnHelp->SetObserver(&btnHelpObserver);
    btnHelp->SetWidgetPosition({ size.x, 0, 0 });

    PushButtonWidget *btnSettings = new PushButtonWidget(size, "Settings");
    if (btnSettings)
    {
        btnSettings->SetObserver(&btnSettingsObserver);
        widgets.AddElement(btnSettings);
        btnSettings->SetWidgetPosition({ size.x * 2, 0, 0 });
    }

    PushButtonWidget *btnGo = new PushButtonWidget({ 450, 150 }, "Go to BATTLE!!!");
    if (btnGo)
    {
        btnGo->SetObserver(&btnGoObserver);
        widgets.AddElement(btnGo);
        Vector2D sizeDesktop = TheInterfaceMgr->GetDesktopSize();
        float x = sizeDesktop.x / 2 - btnGo->GetWidgetSize().x / 2;
        float y = sizeDesktop.y / 2 - btnGo->GetWidgetSize().y / 2;
        btnGo->SetWidgetPosition({ x, y, 0 });
    }
}


void HangarGUI::HandleButtonLanguage(Widget *, const WidgetEventData *data)
{
    if (data->eventType == Pi::EventWidget::Activate)
    {

    }
}


void HangarGUI::HandleButtonHelp(Widget *, const WidgetEventData *data)
{
    if (data->eventType == Pi::EventWidget::Activate)
    {

    }
}


void HangarGUI::HandleButtonSettings(Widget *, const WidgetEventData *data)
{
    if (data->eventType == Pi::EventWidget::Activate)
    {
        
    }
}


void HangarGUI::HandleButtonGo(Widget *, const WidgetEventData *data)
{
    if (data->eventType == Pi::EventWidget::Activate)
    {
        delete this;

        if (TheWorldMgr->LoadWorld("worlds/world1") != Pi::WorldResult::Okay)
        {
            TheConsoleWindow->AddText("load world failed");
        }
        else
        {
            TheConsoleWindow->AddText("load world is ok!");
        }
    }
}


HangarGUI::~HangarGUI()
{
    Hide();

    for (Widget *widget : widgets)
    {
        delete widget;
    }
}


void HangarGUI::Show()
{
    for (Widget *widget : widgets)
    {
        AppendNewSubnode(widget);
    }
}


void HangarGUI::Hide()
{
    for (Widget *widget : widgets)
    {
        RemoveSubnode(widget);
    }
}
