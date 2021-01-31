#include "stdafx.h"


using namespace Pi;


static String<> commandLine;


PI_ENTER_POINT(Client); //-V2511 //-V2567


static void ThreadConnect(std::string fullAddress);


static void WriteErrorRun()
{
    LOG_ERROR("For run type \"Client.exe -hangar:xxx.xxx.xxx.xxx:yyyyy\"");
}


Client::Client() : Application(), Singleton<Client>(TheGame)
{
    Log::Create("Client.log");

    std::vector<std::string> words;

    SU::SplitToWords(commandLine.c_str(), commandLine.Length(), words);

    if (words.size() != 1 || !SU::BeginWith(words[0].c_str(), "-hangar:"))
    {
        WriteErrorRun();

        needQuit = true;
    }

    gConfig.Load("Client.conf");

//    TheHangar = new HangarServer();

//    std::string fullAddress(&words[0][std::strlen("-hangar:")]);
//
//    std::thread thread(ThreadConnect, fullAddress);
//    thread.detach();
}


static void ThreadConnect(std::string fullAddress)
{
    TheHangar->Connect(fullAddress);
}


Client::~Client()
{
//    SAFE_DELETE(TheHangar);
    gConfig.Unload();
    Log::Destroy();
}


void Client::ApplicationTask()
{
    if (needQuit)
    {
        TheEngine->Quit();
    }
}
