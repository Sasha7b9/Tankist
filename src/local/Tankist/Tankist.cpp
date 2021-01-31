#include "stdafx.h"


static String<> commandLine;

PI_ENTER_POINT(Tankist); //-V2567 //-V2511

static void ThreadConnect();


Tankist::Tankist() :  Application(),  Singleton<Tankist>(TheGame),
    settingsCommandObserver(this, &Tankist::HandleSettingsCommand)
{
    Log::Create("Tankist.log");

    gConfig.Load("Tankist.conf");

    TheMainWindow = new MainWindow(); //-V2511

    TheInterfaceMgr->AddWidget(TheMainWindow);

    std::thread thread(ThreadConnect);
    thread.detach();

	TheEngine->AddCommand(new Command("settings", &settingsCommandObserver)); //-V2511
}


static void ThreadConnect()
{
    gMaster.Connnect();

    TheMainWindow->ConnectToMasterIsOK();
}


Tankist::~Tankist()
{
    delete TheAttemptConnectionWindow; //-V2511
    gMaster.Destroy();
    gConfig.Unload();
    Log::Destroy();
    delete TheMainWindow; //-V2511
}


void Tankist::ApplicationTask()
{
//    TheMainWindow->Update();
}


void Tankist::HandleSettingsCommand(Command *, pchar )
{
	GraphicsSettingsWindow::Open();
}


void Tankist::HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &, const void *)
{
    TheAttemptConnectionWindow->Hide();

    switch (event)
    {
    case ConnectionEvent::AttemptFailed:
        TheFailedConnectionWindow->Open();
        break;
    case ConnectionEvent::ClientOpened:
        break;
    case ConnectionEvent::ServerAccepted:
        {
            String<> command("start Client.exe $ipHangar=\"");
            command += TheMainWindow->GetHangarAddress();
            command += "\"; $playerName=\"";
            command += TheMainWindow->GetLogin();
            command += "\"";
            system(command.c_str()); //-V2509
            TheEngine->Quit();
        }
        break;
    case ConnectionEvent::ServerClosed:
        break;
    case ConnectionEvent::ClientClosed:
        break;
    case ConnectionEvent::ServerTimedOut:
        break;
    case ConnectionEvent::ClientTimedOut:
        break;
    case ConnectionEvent::QueryReceived:
        break;
    }
}
