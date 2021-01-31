#include "stdafx.h"


using namespace Pi;


MainServer::MainServer()
{

}


void MainServer::Create()
{
    TheMainServer = new MainServer(); //-V2511
}


void MainServer::Destroy()
{
    delete TheMainServer; //-V2511
}


bool MainServer::RequestConnect(pchar strAddress, uint16 port)
{
    ThePlayer = nullptr;

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(0);
    TheNetworkMgr->SetBroadcastPortNumber(port);

    TheMessageMgr->BeginMultiplayerGame(false);

    NetworkAddress address = MessageMgr::StringToAddress(strAddress);
    address.SetPort(port);

    return (TheMessageMgr->Connect(address) == NetworkResult::Okay);
}


void MainServer::RequestPing()
{
    SendMessage(PlayerType::Server, ServerPingMessage());
}


void MainServer::SendMessage(PlayerKey key, const Message &message) const
{
    TheMessageMgr->SendMessage(key, message);
}


void MainServer::SendMessage(const Message &message) const
{
    TheMessageMgr->SendMessage(PlayerType::Server, message);
}


void MainServer::SendChatMessage(pchar text)
{
    SendMessage(PlayerType::Server, MainChatMessage(text, nullptr));
}


void MainServer::RequesBattle()
{
    PiLOG_WRITE("Disconnect from hangar");

    auto selfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_BATTLE);
    uint16 port = ConnectorTCP::ParseAddress(selfAddress.c_str()).second;

    AttemptConnectionWindow::Open();

    TheMessageMgr->EndGame();

    TheNetworkMgr->NetworkTask();

    TheInterfaceMgr->RemoveWidget(TheHangarWindow);

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(0);
    TheNetworkMgr->SetBroadcastPortNumber(port);

    TheMessageMgr->BeginMultiplayerGame(false);

    NetworkAddress address = MessageMgr::StringToAddress(TheEngine->GetVariable("ipServer")->GetValue().c_str()); //-V522
    address.SetPort(port);

    TheMessageMgr->Connect(address);

    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);
}
