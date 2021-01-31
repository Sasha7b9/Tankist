#include "stdafx.h"
#include "Network/Messages/_MessagesHangar.h"
#include "Network/Messages/_MessagesServer.h"
#include "Chat.h"
#include "Hangar.h"


void Hangar::HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &, const void *)
{
    switch (event)
    {
    case ConnectionEvent::AttemptFailed:
        break;

    case ConnectionEvent::ClientOpened:
        break;
    case ConnectionEvent::ServerAccepted:
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


void Hangar::HandlePlayerEvent(PlayerEvent::E, Player *, const void *)
{

}


void Hangar::HandleGameEvent(GameEvent, const void *)
{

}


Message *Hangar::CreateMessage(MessageType::E type, Decompressor &) const //-V2506
{
    switch (type)
    {
    case MessageType::ServerKill:
        return new ServerKillMessage(); //-V2511
        break;

    case MessageType::ServerPing:
        return new ServerPingMessage(); //-V2511
        break;

    case MessageType::PlayerName:
        return new PlayerNameMessage(); //-V2511
        break;

    case MessageType::MainChat:
        return new MainChatMessage(); //-V2511
        break;
    case MessageType::RequestBattle:
        return new RequestBattleMessage(); //-V2511
        break;
    }

    return nullptr;
}


void Hangar::ReceiveMessage(Player *sender, const NetworkAddress &, const Message *message) //-V2558
{
    switch (message->GetMessageType())
    {
    case MessageType::ServerKill:
        TheMessageMgr->SendMessageAll(ServerMessageMessage("Server will now be destroyed"));
        isRunning = false;
        break;

    case MessageType::ServerPing:
        TheMessageMgr->SendMessage(sender->GetKey(), *message);
        break;

    case MessageType::PlayerName:
        {
            TheMessageMgr->GetPlayer(sender->GetPlayerKey())->SetPlayerName(static_cast<const PlayerNameMessage *>(message)->GetName());
            String<> chatMessage = "";
            chatMessage += TheMessageMgr->GetPlayer(sender->GetPlayerKey())->GetPlayerName();
            chatMessage += " connected to chat";
            TheChat->AddMessage(chatMessage.c_str());
        }
        break;

    case MessageType::MainChat:
        {
            String<> chatMessage(sender->GetPlayerName());
            chatMessage += " : ";
            chatMessage += static_cast<const MainChatMessage *>(message)->text.c_str();
            TheChat->AddMessage(chatMessage.c_str());
        }
        break;

    case MessageType::RequestBattle:
        break;
    }
}
