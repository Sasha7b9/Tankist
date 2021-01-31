#include "stdafx.h"


void Client::HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &address, const void *)
{
    switch (event)
    {
    case ConnectionEvent::AttemptFailed:
        break;

    case ConnectionEvent::ClientOpened:
        break;

    case ConnectionEvent::ServerAccepted:
        {
            auto addressHangar = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);
            uint16 portHangar = ConnectorTCP::ParseAddress(addressHangar.c_str()).second;

            auto addressBattle = gMaster.GetValue(MASTER_GET_ADDRESS_BATTLE);
            uint16 portBattle = ConnectorTCP::ParseAddress(addressBattle.c_str()).second;

            if (address.GetPort() == portHangar)
            {
                TheMainServer->SendMessage(PlayerType::Server, PlayerNameMessage(TheEngine->GetVariable("playerName")->GetValue().c_str())); //-V522
            }
            else if (address.GetPort() == portBattle) //-V2516
            {
                TheAttemptConnectionWindow->Close();
                TheGame->LoadWorld("worlds/world1");
                TheMessageMgr->SendMessage(PlayerType::Server, RespawnRequestMessage());
            }
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

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


Message *Client::CreateMessage(MessageType::E type, Decompressor &) const //-V2506
{
    switch (type)
    {
    case MessageType::ServerMessage:
        return new ServerMessageMessage(); //-V2511
        break;

    case MessageType::ServerPing:
        return new ServerPingMessage(); //-V2511
        break;

    case MessageType::ServerInfo:
        return new ServerInfoMessage(); //-V2511
        break;

    case MessageType::MainChat:
        return new MainChatMessage(); //-V2511
        break;

    case MessageType::PendingAcknowledgePackets:
        return new PendingAcknowledgePacketsMessage(); //-V2511
        break;

    case MessageType::Movement:
        return new MovementMessage(); //-V2511
        break;

    case MessageType::RespawnDo:
        return new RespawnDoMessage(); //-V2511
        break;

    case MessageType::RemovePlayer:
        return new RemovePlayerMessage(); //-V2511
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }

    return nullptr;
}


void Client::ReceiveMessage(Player *, const NetworkAddress &, const Message *message)
{
    switch (message->GetMessageType())
    {
    case MessageType::Movement:
        if (TheController)
        {
            uint flag = static_cast<const MovementMessage *>(message)->direction;

            TheController->SetMovementFlags(TheController->GetMovementFlags() | flag);
        }
        break;

    case MessageType::ServerPing:
        TheNetworkWidget->SetPing(static_cast<const ServerPingMessage *>(message)->GetPing());
        break;

    case MessageType::ServerInfo:
        TheNetworkWidget->SetServerInfo(static_cast<const ServerInfoMessage *>(message));
        break;

    case MessageType::MainChat:
        TheHangarWindow->chatWidget->AddMessage(static_cast<const MainChatMessage *>(message)->FullText());
        break;

    case MessageType::PendingAcknowledgePackets:
        PiLOG_WRITE(static_cast<const PendingAcknowledgePacketsMessage *>(message)->GetMessage().c_str());
        break;

    case MessageType::RespawnDo:
        CreatePlayer(static_cast<const RespawnDoMessage *>(message));
        break;

    case MessageType::RemovePlayer:
        {
            PlayerKey key = static_cast<const RemovePlayerMessage *>(message)->key;
            GamePlayer *p = players.First();
            while(p)
            {
                if(p->key == key)
                {
                    p->controller->GetTargetNode()->Disable();
                    players.Remove(p);
                    break;
                }

                p = p->Next();
            }
        }
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


void Client::HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *) //-V2558
{
    switch (event)
    {
    case PlayerEvent::Connected:
        break;

    case PlayerEvent::Disconnected:
        break;

    case PlayerEvent::TimedOut:
        break;

    case PlayerEvent::Initialized:
        PiLOG_WRITE("PlayerEvent::Initialized %d", player->GetPlayerKey());
        break;

    case PlayerEvent::ChatReceived:
        break;

    case PlayerEvent::Renamed:
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


void Client::HandleGameEvent(GameEvent event, const void *)
{
    switch (event) //-V785
    {
    case kGameSynchronized:
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}
