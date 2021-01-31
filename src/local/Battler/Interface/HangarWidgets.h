#pragma once


using namespace Pi;

class ServerInfoMessage;


class NetworkWidget : public Window
{
public:
	NetworkWidget();

	void UpdateState();

	void SetPing(int p);

	void SetServerInfo(const ServerInfoMessage *message);

private:
	static const int numStrings = 8;
	static const float heightString;
	static const int width = 200;
	static const float height;
	TextWidget *textSpeedInServer = nullptr; //-V122
	TextWidget *textSpeedOutServer = nullptr; //-V122
	TextWidget *textNumberPlayers = nullptr; //-V122
	TextWidget *textPing = nullptr; //-V122
	TextWidget *textServerFPS = nullptr; //-V122
	TextWidget *textSpeedIn = nullptr; //-V122
	TextWidget *textSpeedOut = nullptr; //-V122
	TextWidget *textPacketsCount = nullptr;		///< Здесь число пакетов, ожидающих отправки и подтверждения //-V122

	TextWidget *CreateTextWidget(int i);
};


class ChatWidget : public Window
{
public:
	ChatWidget(float height);

	void AddMessage(pchar message);
private:
	static const float width;

	EditTextWidget *lineEdit = nullptr; //-V122
	TextWidget *historyWidget = nullptr; //-V122

	bool HandleKeyboardEvent(const KeyboardEventData *) override;
};


class HangarWindow : public Window
{
public:
	HangarWindow();

	ChatWidget *chatWidget = nullptr; //-V122

private:

	PushButtonWidget *btnGoBattle = nullptr; //-V122
	PushButtonWidget *btnHelp = nullptr; //-V122
	PushButtonWidget *btnSite = nullptr; //-V122
	PushButtonWidget *btnSettings = nullptr; //-V122
	PushButtonWidget *btnUsers = nullptr; //-V122

	virtual void HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) override;
};


/// Окно ожидания соединения с сервером
class AttemptConnectionWindow : public Window, public Completable<AttemptConnectionWindow>, public Singleton<AttemptConnectionWindow>
{
public:
    static void Open();
private:
    TextWidget *text = nullptr; //-V122
    AttemptConnectionWindow();
    virtual void Move() override;
};
