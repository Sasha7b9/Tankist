#include "stdafx.h"
#include "Network/Messages/_MessagesHangar.h"
#include "Chat.h"


ChatMessage::ChatMessage(pchar text) : message(text)
{
    TimeMgr::GetDateTime(&dateTime);
}


Chat::Chat() : Singleton(TheChat)
{

}


void Chat::Create()
{
    new Chat(); //-V2511
}


void Chat::AddMessage(pchar message)
{
    ChatMessage *msg = new ChatMessage(message); //-V2511

    TheTimeMgr->GetDateTime(&msg->dateTime); //-V522

    history.Append(msg);

    Player *player = TheMessageMgr->GetFirstPlayer();

    while (player)
    {
        if (player->GetPlayerKey() != TheMessageMgr->GetLocalPlayer()->GetPlayerKey())
        {
            PlayerStruct *str = players.Find(player->GetKey());

            if (str)
            {
                SendMessages(str);
            }
            else
            {
                str = new PlayerStruct(player); //-V2511
                players.Insert(str);
                SendMessages(str);
            }
        }

        player = player->Next();
    }
}


void Chat::SendMessages(PlayerStruct *str)
{
    int numMessages = history.GetElementCount() - str->sended;

    for (int num = history.GetElementCount() - numMessages; num < history.GetElementCount(); num++)
    {
        MainChatMessage message(history[num]->message.c_str(), &history[num]->dateTime);

        str->player->SendMessage(message);
    }

    str->sended = history.GetElementCount();
}
