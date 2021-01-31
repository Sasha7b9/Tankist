#include "stdafx.h"


const float ChatWidget::width = 500.0F;

const float NetworkWidget::heightString = 16.0F;
const float NetworkWidget::height = NetworkWidget::numStrings * NetworkWidget::heightString; //-V2564


#define HEIGHT_BUTTON 50
#define WIDTH_BUTTON 150
#define SIZE_BUTTON {WIDTH_BUTTON, HEIGHT_BUTTON}

#define ENTER_FONT "font/Gui"


HangarWindow::HangarWindow() : Window({ 1000, 1000 }, nullptr, Window::Flag::_None | Window::Flag::Passive)
{
	SetWidgetPosition({ 0, 0, 0 });
	SetWidgetSize(Vector2D(TheEngine->GetVariable("displayWidth")->GetIntegerValue(), TheEngine->GetVariable("displayHeight")->GetIntegerValue())); //-V522 //-V2564
	Vector2D sizeWidget = GetWidgetSize();

	btnHelp = new PushButtonWidget(SIZE_BUTTON, "Help"); //-V2511
	btnHelp->SetWidgetPosition({ 0, 0, 0 }); //-V522
	btnHelp->SetFont("font/Title");

	btnSite = new PushButtonWidget(SIZE_BUTTON, "Site"); //-V2511
	btnSite->SetWidgetPosition({ WIDTH_BUTTON + 10, 0, 0 }); //-V522
	btnSite->SetFont("font/Title");

	btnSettings = new PushButtonWidget(SIZE_BUTTON, "Settings"); //-V2511
	btnSettings->SetWidgetPosition({ (WIDTH_BUTTON + 10) * 2, 0, 0 }); //-V522
	btnSettings->SetFont("font/Title");

	btnUsers = new PushButtonWidget(SIZE_BUTTON, "Users"); //-V2511
	btnUsers->SetWidgetPosition({ (WIDTH_BUTTON + 10) * 3, 0, 0 }); //-V522
	btnUsers->SetFont("font/Title");

	chatWidget = new ChatWidget(sizeWidget.y); //-V2511
	chatWidget->SetWidgetPosition({ sizeWidget.x - chatWidget->GetWidgetSize().x, 0, 0 }); //-V522

	btnGoBattle = new PushButtonWidget({ 300, 100 }, "GO FIGHT"); //-V2511
	btnGoBattle->SetWidgetPosition({ (sizeWidget.x - chatWidget->GetWidgetSize().x) / 2 - btnGoBattle->GetWidgetSize().x / 2, sizeWidget.y / 2 - btnGoBattle->GetWidgetSize().y / 2, 0 }); //-V522 //-V2564
	btnGoBattle->SetFont("font/Title");

	AppendSubnode(btnUsers);
	AppendSubnode(btnSettings);
	AppendSubnode(btnSite);
	AppendSubnode(btnHelp);
	AppendSubnode(btnGoBattle);
	AppendSubnode(chatWidget);

    TheNetworkWidget = new NetworkWidget(); //-V2511
    TheNetworkWidget->SetWidgetPosition({ 0, sizeWidget.y - TheNetworkWidget->GetWidgetSize().y, 0 }); //-V522

	TheInterfaceMgr->AddWidget(TheNetworkWidget);
}


void HangarWindow::HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) //-V2558
{
	if (eventData->eventType == EventWidget::Activate)
	{
		if (widget == btnSettings)
		{
			GraphicsSettingsWindow::Open();
		}
		else if(widget == btnGoBattle) //-V2516
		{
			TheMainServer->RequesBattle();
		}
	}
}


NetworkWidget::NetworkWidget() : Window({ width, height }, nullptr, Window::Flag::Plain | Window::Flag::Background | Window::Flag::Passive)
{
	QuadWidget *quad = new QuadWidget({ width, height }); //-V2511
	quad->SetWidgetColor({ 0.5F, 0.5F, 1.0F }); //TODO: V2517 https://www.viva64.com/ru/w/v2517/ Literal suffix 'f' should not contain lowercase characters. //-V522

	textPing = CreateTextWidget(0);
	textNumberPlayers = CreateTextWidget(1);
	textServerFPS = CreateTextWidget(2);
	textSpeedIn = CreateTextWidget(3);
	textSpeedOut = CreateTextWidget(4); //-V112
    textSpeedInServer = CreateTextWidget(5);
    textSpeedOutServer = CreateTextWidget(6);
	textPacketsCount = CreateTextWidget(7);

	AppendSubnode(quad);
	AppendSubnode(textNumberPlayers);
	AppendSubnode(textPing);
	AppendSubnode(textServerFPS);
	AppendSubnode(textSpeedIn);
	AppendSubnode(textSpeedOut);
	AppendSubnode(textPacketsCount);
	AppendSubnode(textSpeedInServer);
	AppendSubnode(textSpeedOutServer);
}


TextWidget *NetworkWidget::CreateTextWidget(int i)
{
    TextWidget *widget = new TextWidget({ width, height / numStrings }); //-V2564 //-V2511
    widget->SetWidgetPosition({ 0, static_cast<float>(i) * heightString + 2, 0 }); //-V522 //-V2564
    widget->SetFont("font/Gui");
    widget->SetTextAlignment(Pi::TextAlignment::Center);
	return widget;
}


void NetworkWidget::SetPing(int ping)
{
	if (ping != -1)
	{
		char buffer[100];
		snprintf(buffer, 99, "Ping : %d", ping);
		textPing->SetText(buffer);
	}
	else
	{
		textPing->SetText("Ping : not available");
	}
}


void NetworkWidget::SetServerInfo(const ServerInfoMessage *message)
{
    if(message->count > 0)
    {
		textNumberPlayers->SetText(Text::Format("Players on server : %d", message->count));
    }
    else
    {
        textNumberPlayers->SetText("Gamers on server : not available");
    }

	textServerFPS->SetText(Text::Format("Server FPS : %d", message->fps));

	textSpeedInServer->SetText(Text::Format("Server in : %ud / %ud", message->receivedBytes, message->speedIn));

	textSpeedOutServer->SetText(Text::Format("Server out : %ud / %ud", message->sendedBytes, message->speedOut));
}


void NetworkWidget::UpdateState()
{
	static uint prevTime = 0;

	if (TheTimeMgr->GetSystemAbsoluteTime() > prevTime + 1000)
	{
		prevTime = TheTimeMgr->GetSystemAbsoluteTime();

		TheMainServer->RequestPing();
	}

	static uint timeSec = 0;				///< Ќачало измерени€ секунды
	static uint bytesRecvOnStartSec = 0;	///<  оличество прин€тых байт на начало секунды
	static uint bytesSendOnStartSec = 0;	///<  оличество переданных байт на начало секунды

	static uint speedRecv = 0;
	static uint speedSend = 0;

	uint recvBytes = TheNetworkMgr->GetBytesRecv();
	uint sendBytes = TheNetworkMgr->GetBytesSend();

	if(TheTimeMgr->GetAbsoluteTime() >= timeSec + 1000)
	{
		speedRecv = recvBytes - bytesRecvOnStartSec;
		speedSend = sendBytes - bytesSendOnStartSec;
		bytesRecvOnStartSec = recvBytes;
		bytesSendOnStartSec = sendBytes;
		timeSec = TheTimeMgr->GetAbsoluteTime();
	}

	textSpeedIn->SetText(Text::Format("Bytes in : %ud / %ud", recvBytes, speedRecv));
	textSpeedOut->SetText(Text::Format("Bytes out : %ud / %ud", sendBytes, speedSend));

	textPacketsCount->SetText(Text::Format("Packets wait : %d", TheNetworkMgr->GetPacketCount()));
}


ChatWidget::ChatWidget(float height) : Window({ width, height }, nullptr, Window::Flag::Plain | Window::Flag::Background | Window::Flag::Passive)
{
	QuadWidget *quad = new QuadWidget({ width, height }); //-V2511
	quad->SetWidgetColor({ 0.5F, 0.5F, 1.0F }); //-V522

	AppendSubnode(quad);

	lineEdit = new EditTextWidget({ width - 6, 10 }, 1024, "font/Gui"); //-V2564 //-V2511
	lineEdit->SetWidgetPosition({ 3, quad->GetWidgetSize().y - 13, 0 }); //-V522 //-V2564
	lineEdit->SetEditTextFlags(Pi::EditTextFlags::FocusPlain | Pi::EditTextFlags::Overflow);

	historyWidget = new TextWidget({ width - 10, height - 20 }, "", "font/Gui"); //-V2564 //-V2511
	historyWidget->SetWidgetPosition({ 3, 3, 0 }); //-V522
	historyWidget->SetTextFlags(Pi::TextFlag::Wrapped);

	quad->AppendSubnode(lineEdit);
	quad->AppendSubnode(historyWidget);
}


bool ChatWidget::HandleKeyboardEvent(const KeyboardEventData *eventData) //-V2506
{
	Pi::EventKeyboard::S eventType = eventData->eventType;

	if (eventType == Pi::EventKeyboard::KeyDown)
	{
		Pi::KeyCode::E keyCode = eventData->keyCode;

		if ((keyCode == Pi::KeyCode::Enter) && (lineEdit->GetText()[0] != 0)) //-V2563
		{
			TheMainServer->SendChatMessage(lineEdit->GetText());

			lineEdit->SetText("");

			return true;
		}
	}

	return Window::HandleKeyboardEvent(eventData);
}


void ChatWidget::AddMessage(pchar message)
{
	String<> text(historyWidget->GetText());
	text += message;
	text += "\n";

	historyWidget->SetText(text);
}


void AttemptConnectionWindow::Open()
{
    if (TheAttemptConnectionWindow)
    {
        TheInterfaceMgr->SetActiveWindow(TheAttemptConnectionWindow);
        TheAttemptConnectionWindow->Show();
    }
    else
    {
        TheInterfaceMgr->AddWidget(new AttemptConnectionWindow()); //-V2511
    }
}


AttemptConnectionWindow::AttemptConnectionWindow() :
    Window({ 300, 100 }, "Attempt connection", Window::Flag::Center | Window::Flag::Modal | Window::Flag::Background | Window::Flag::Plain | Window::Flag::Passive),
    Singleton<AttemptConnectionWindow>(TheAttemptConnectionWindow)
{
    text = new TextWidget({ 300, 100 }); //-V2511
    text->SetTextFlags(TextFlag::Wrapped); //-V522
    text->SetWidgetPosition({ 0, 30, 0 });
    text->SetFont(ENTER_FONT);
    text->SetTextAlignment(TextAlignment::Center);
    AppendSubnode(text);
}


void AttemptConnectionWindow::Move()
{
    uint num = (TheTimeMgr->GetAbsoluteTime() / 100) % 50;

    String<> string("Attempt to server.\nPlease wait.\n");

    for (uint i = 0; i < num; i++)
    {
        string.Append(".", 1);
    }

    text->SetText(string.c_str());
}
