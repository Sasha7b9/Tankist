#include "stdafx.h"

#define SETTING_LANG 'lang'

#define HEIGHT_BUTTON 25
#define WIDTH_BUTTON 125
#define SIZE_BUTTON {WIDTH_BUTTON, HEIGHT_BUTTON}

#define ENTER_FONT "font/Gui"
#define MAIN_FONT  "font/Title"

#define LENGTH_LE  125


MainWindow::MainWindow() : Window({ 1000, 1000 }, nullptr, Window::Flag::_None)
{
	SetWidgetPosition({ 0, 0, 0 });
	SetWidgetSize(Vector2D(TheEngine->GetVariable("displayWidth")->GetIntegerValue(), TheEngine->GetVariable("displayHeight")->GetIntegerValue())); //-V522 //-V2564
	Vector2D sizeWidget = GetWidgetSize();

	float y = 30.0F;

	float x = 40.0F;

	buttonLanguage = new PushButtonWidget(SIZE_BUTTON, "Language : EN"); //-V2511
	buttonLanguage->SetWidgetPosition({ x, y, 0 }); //-V522
	buttonLanguage->SetFont(MAIN_FONT);

	buttonHelp = new PushButtonWidget(SIZE_BUTTON, "Help"); //-V2511
	buttonHelp->SetWidgetPosition({ x + WIDTH_BUTTON + 10, y, 0 }); //-V522 //-V2564
	buttonHelp->SetFont(MAIN_FONT);

	buttonSite = new PushButtonWidget(SIZE_BUTTON, "Site"); //-V2511
	buttonSite->SetWidgetPosition({ x + WIDTH_BUTTON * 2 + 20, y, 0 }); //-V522 //-V2564
	buttonSite->SetFont(MAIN_FONT);

	y = 100.0F;

	TextWidget *text = new TextWidget({75, 20}, "Login", ENTER_FONT); //-V2511
	text->SetWidgetPosition({ x, y, 0 }); //-V522
	text->SetWidgetColor(ColorRGBA(1.0F, 1.0F, 1.0F, 1.0F));
	AppendNormalWidget(text);

	lineEditLogin = new EditTextWidget({ LENGTH_LE, 15 }, 20, ENTER_FONT); //-V2511
	lineEditLogin->SetWidgetPosition({ x + 70, y, 0 }); //-V522 //-V2564
	lineEditLogin->SetText("auto");
	lineEditLogin->Disable();

	text = new TextWidget({75, 20}, "Password", ENTER_FONT); //-V2511
	text->SetWidgetPosition({x, y + 30, 0}); //-V2564
	text->SetWidgetColor({1.0F, 1.0F, 1.0F});
	AppendNormalWidget(text);
		
	lineEditPassword = new EditTextWidget({ LENGTH_LE, 15 }, 20, ENTER_FONT); //-V2511
	lineEditPassword->SetWidgetPosition({ x + 70, y + 30, 0 }); //-V522 //-V2564
	lineEditPassword->SetText("auto");
	lineEditPassword->Disable();

	text = new TextWidget({75, 20}, "Address", ENTER_FONT); //-V2511
	text->SetWidgetPosition({x, y + 60, 0}); //-V2564
	text->SetWidgetColor({1.0F, 1.0F, 1.0F});
	AppendNormalWidget(text);

	lineEditAddress = new EditTextWidget({ LENGTH_LE, 15 }, 20, ENTER_FONT); //-V2511
	lineEditAddress->SetWidgetPosition({ x + 70, y + 60, 0 }); //-V522 //-V2564
	lineEditAddress->Disable();

	buttonConnect = new PushButtonWidget(SIZE_BUTTON, "Connect"); //-V2511
	buttonConnect->SetWidgetPosition({ 250, y + 25, 0 }); //-V522 //-V2564
	buttonConnect->SetFont(MAIN_FONT);

	buttonRegistration = new PushButtonWidget(SIZE_BUTTON, "Registration"); //-V2511
	buttonRegistration->SetWidgetPosition({ x, y + 150, 0 }); //-V522 //-V2564
	buttonRegistration->SetFont(MAIN_FONT);

	y = 330.0F;

	buttonExtra = new PushButtonWidget(SIZE_BUTTON, "Extra"); //-V2511
	buttonExtra->SetWidgetPosition({ 30, y, 0 }); //-V522
	buttonExtra->SetFont(MAIN_FONT);

	buttonExit = new PushButtonWidget(SIZE_BUTTON, "Exit"); //-V2511
	buttonExit->SetWidgetPosition({ 330, y, 0 }); //-V522
	buttonExit->SetFont(MAIN_FONT);

	AppendBothWidget(buttonExit);
	AppendBothWidget(buttonExtra);

    AppendNormalWidget(lineEditLogin);
    AppendNormalWidget(lineEditPassword);
    AppendNormalWidget(lineEditAddress);
    AppendNormalWidget(buttonHelp);
    AppendNormalWidget(buttonLanguage);
	AppendNormalWidget(buttonRegistration);
	AppendNormalWidget(buttonConnect);
	AppendNormalWidget(buttonSite);

	LoadSettings();

	SetExtraMode();

	TheAttemptConnectionWindow = new AttemptConnectionWindow(); //-V2511

	AppendSubnode(TheAttemptConnectionWindow);

	BringToFront(TheAttemptConnectionWindow);
}


void MainWindow::LoadSettings()
{
	Variable *variable = TheEngine->GetVariable("login");
	lineEditLogin->SetText(variable ? variable->GetValue().c_str() : "login");

	variable = TheEngine->GetVariable("password");
	lineEditPassword->SetText(variable ? variable->GetValue().c_str() : "password");
}


void MainWindow::AppendNormalWidget(Widget *widget)
{
	AppendSubnode(widget);
	widgetsNormalMode.Append(widget);
}


void MainWindow::AppendBothWidget(Widget *widget)
{
	AppendSubnode(widget);
}


void MainWindow::HandleWidgetEvent(Widget *widget, const Pi::WidgetEventData *data) //-V2558
{
	if(data->eventType == EventWidget::Change)
	{
	    if (widget == lineEditAddress)
	    {
			TheEngine->SetValueVariable("addressIP", lineEditAddress->GetText());
	    }

		if (widget == lineEditPassword)
		{
			TheEngine->SetValueVariable("password", lineEditPassword->GetText());
		}

		if (widget == lineEditLogin)
		{
			TheEngine->SetValueVariable("login", lineEditLogin->GetText());
		}
	}

	if (data->eventType == EventWidget::Activate)
	{
		if (widget == buttonLanguage)
		{
			language++;
			language &= 0x1;
			buttonLanguage->SetText(language ? "Language : RU" : "Language : EN");
		}

		if (widget == buttonExit)
		{
			ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());
			TheEngine->Quit();
		}

		if (widget == buttonSite)
		{
			TheEngine->OpenExternalWebBrowser("http://78.24.217.211/");
		}

        if (widget == buttonExtra)
        {
            extra = (extra + 1) & 0x1;
            SetExtraMode();
        }

        if (widget == buttonConnect)
        {
			ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());
            AttemptConnection();
        }
	}
}


void MainWindow::SetExtraMode()
{
	if (extra)
	{
		for (Widget* widget : widgetsNormalMode)
		{
			widget->Hide();
		}

		for (Widget* widget : widgetsExtraMode)
		{
			widget->Show();
		}
	}
	else
	{
		for (Widget* widget : widgetsExtraMode)
		{
			widget->Hide();
		}

		for (Widget* widget : widgetsNormalMode)
		{
			widget->Show();
		}
	}
}


void MainWindow::AttemptConnection()
{
//	auto selfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);
//	uint16 port = ConnectorTCP::ParseAddress(selfAddress.c_str()).second;
//
//	TheNetworkMgr->SetProtocol(kGameProtocol);
//	TheNetworkMgr->SetPortNumber(0);
//	TheNetworkMgr->SetBroadcastPortNumber(port);
//
//	NetworkAddress address = MessageMgr::StringToAddress(lineEditAddress->GetText());
//	address.SetPort(port);
//
//	TheMessageMgr->Connect(address);
}


pchar MainWindow::GetHangarAddress() const
{
	return lineEditAddress->GetText();
}


pchar MainWindow::GetLogin() const
{
	return lineEditLogin->GetText();
}


void MainWindow::ConnectToMasterIsOK()
{
	if (TheAttemptConnectionWindow)
	{
		TheInterfaceMgr->RemoveWidget(TheAttemptConnectionWindow);
	}

	connectedToMasterIsOK = true;
}


void MainWindow::Move()
{
	Window::Move();

	if (connectedToMasterIsOK && lineEditAddress->GetTextLength() == 0)
	{
        std::string addressHangar = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);

		lineEditAddress->SetText(addressHangar.c_str());

		gMaster.Destroy();
	}
}


AttemptConnectionWindow::AttemptConnectionWindow() :
	Window({ (float)TheEngine->GetVariable("displayWidth")->GetIntegerValue(), (float)TheEngine->GetVariable("displayHeight")->GetIntegerValue() },
		"Attempt connection", Window::Flag::Center | Window::Flag::Modal | Window::Flag::Background | Window::Flag::Plain),
	Singleton<AttemptConnectionWindow>(TheAttemptConnectionWindow)
{
	text = new TextWidget({ (float)TheEngine->GetVariable("displayWidth")->GetIntegerValue(), (float)TheEngine->GetVariable("displayHeight")->GetIntegerValue() }); //-V2511
	text->SetTextFlags(TextFlag::Wrapped); //-V522
	text->SetWidgetPosition({ 0, 30, 0 });
	text->SetFont(ENTER_FONT);
	text->SetTextAlignment(TextAlignment::Center);
	AppendSubnode(text);
	Show();
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


FailedConnectionWindow::FailedConnectionWindow() : Window({ 300, 100 }, "Failed connection", Window::Flag::Center | Window::Flag::Modal | Window::Flag::Background | Window::Flag::Plain),
Singleton<FailedConnectionWindow>(TheFailedConnectionWindow)
{
	TextWidget* text = new TextWidget({ 300, 100 }); //-V2511
	text->SetText("Failed connnection to server"); //-V522
	text->SetWidgetPosition({ 0, 20, 0 });
	text->SetFont(ENTER_FONT);
	text->SetTextAlignment(TextAlignment::Center);
	AppendSubnode(text);

	PushButtonWidget* button = new PushButtonWidget({ 100, 25 }, "Close", ENTER_FONT); //-V2511
	button->SetWidgetPosition({ 110, 60, 0 }); //-V522
	AppendSubnode(button);
}


void FailedConnectionWindow::Open()
{
	if (TheFailedConnectionWindow)
	{
		TheInterfaceMgr->SetActiveWindow(TheFailedConnectionWindow);
		TheFailedConnectionWindow->Show();
	}
	else
	{
		TheInterfaceMgr->AddWidget(new FailedConnectionWindow()); //-V2511
	}
}


void FailedConnectionWindow::HandleWidgetEvent(Widget*, const WidgetEventData* eventData)
{
	if (eventData->eventType == EventWidget::Activate)
	{
		Hide();
	}
}

