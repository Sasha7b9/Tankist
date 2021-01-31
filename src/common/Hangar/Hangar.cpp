#include "stdafx.h"
#include "Network/Messages/_MessagesServer.h"
#include "Chat.h"
#include "Hangar.h"
#include "Network/MainServer.h"


static String<> commandLine;

PI_ENTER_POINT(Hangar); //-V2567 //-V2511


Hangar::Hangar() :  Application(),  Singleton<Hangar>(TheGame)
{
    gMaster.Connnect();

    PiLOG_ADDOUT(Logger::Out::Console | Logger::Out::File, "hangar.log");

    PiLOG_WRITE("Hangar log");

    Chat::Create();

    auto setlfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);

    uint16 port = ConnectorTCP::ParseAddress(setlfAddress.c_str()).second;

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(port);
    TheNetworkMgr->SetBroadcastPortNumber(port);
    TheMessageMgr->SetMaxPlayerCount(64);

    TheMessageMgr->BeginMultiplayerGame(true);
}


Hangar::~Hangar()
{
}


void Hangar::ApplicationTask() //-V2506
{
    static uint prevTime = 0;

    static uint speedIn = 0;
    static uint speedOut = 0;

    CalculateTraffic(&speedIn, &speedOut);

    if (TheTimeMgr->GetAbsoluteTime() > prevTime + 500)
    {
        prevTime = TheTimeMgr->GetAbsoluteTime();

        TheMessageMgr->SendMessage(PlayerType::Clients, ServerInfoMessage(&speedIn, &speedOut));
    }


    if (!isRunning)
    {
        Player *player = TheMessageMgr->GetFirstPlayer();

        while (player)
        {
            if (player->ExistMessagesForSend())
            {
                return;
            }

            player = player->Next();
        }

        TheEngine->Quit();
    }
}


void Hangar::CalculateTraffic(uint *speedIn, uint *speedOut)
{
    static int prevSend = 0;    // Передано байт в текущую секунду
    static int prevRecv = 0;    // Принято байт в текущую секунду
    static uint time = 0;       // Время начала текущей секунды

    if(TheTimeMgr->GetAbsoluteTime() >= time + 1000)
    {
        *speedIn = TheNetworkMgr->GetBytesRecv() - prevRecv;
        *speedOut = TheNetworkMgr->GetBytesSend() - prevSend;

        prevRecv = TheNetworkMgr->GetBytesRecv();
        prevSend = TheNetworkMgr->GetBytesSend();

        time = TheTimeMgr->GetAbsoluteTime();
    }
}
