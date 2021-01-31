#include "stdafx.h"
#include "GameGUI.h"



static TextWidget *textChat = nullptr;
static TextWidget *textPing = nullptr;
static Array<String<> > strings;



/// Разместить строки в TextWidget.
static void ReplaceStrings();



GameGUI::GameGUI()
{
    textChat = new TextWidget({ 200, 1000 });
    if (textChat)
    {
        textChat->SetFont("font/Gui");
        textChat->SetWidgetColor({ 0.0F, 0.0F, 0.0F });
        textChat->SetWidgetPosition({ 0.0F, 0.0F, 0.0F });
        textChat->SetTextFlags(textChat->GetTextFlags() | Pi::TextFlag::Wrapped);

        TheInterfaceMgr->AddWidget(textChat);
    }

    textPing = new TextWidget({ 100, 20 });
    if (textPing)
    {
        textPing->SetFont("font/Gui");
        textPing->SetWidgetColor({ 0.0F, 0.0F, 0.0F });
        textPing->SetWidgetPosition({ (float)(TheInterfaceMgr->GetDesktopSize().x - 100), 0.0F, 0.0F });

        TheInterfaceMgr->AddWidget(textPing);
    }

    ReplaceStrings();
}


void GameGUI::AddSystemMessage(const char *text)
{
    strings.AddElement(String<>(text));

    ReplaceStrings();
}


void GameGUI::SetPing(int ping)
{
    if (textPing)
    {
        String<> text(String<>("Ping = ") + String<>(ping) + " ms");

        textPing->SetText(text);
    }
}


static void ReplaceStrings()
{
    if (textChat)
    {
        textChat->SetText("");

        for (String<> &line : strings)
        {
            const char *history = textChat->GetText();

            textChat->SetText(String<>(history) + line + "\n[INIT][LEFT]");

        }
    }
}
