#pragma once


class PushButton;


class HangarGUI : public Window
{
public:
    HangarGUI();
    ~HangarGUI();

    void Show();

    void Hide();

    void HandleButtonGo(Widget *, const WidgetEventData *);

private:
    WidgetObserver<HangarGUI> btnLanguageObserver;
    WidgetObserver<HangarGUI> btnHelpObserver;
    WidgetObserver<HangarGUI> btnSettingsObserver;
    WidgetObserver<HangarGUI> btnGoObserver;

    Array<Widget*> widgets;

    void HandleButtonLanguage(Widget *, const WidgetEventData *);
    void HandleButtonHelp(Widget *, const WidgetEventData *);
    void HandleButtonSettings(Widget *,const WidgetEventData *);
    
    void CreateButtons();
};
