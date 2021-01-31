#include "stdafx.h"


ServerKillMessage::ServerKillMessage() : Message(MessageType::ServerKill)
{

}

ServerKillMessage::~ServerKillMessage()
{

}


void ServerKillMessage::Compress(Compressor &) const
{

}


bool ServerKillMessage::Decompress(Decompressor &)
{
    return true;
}


ServerMessageMessage::ServerMessageMessage() : Message(MessageType::ServerMessage)
{

}


ServerMessageMessage::ServerMessageMessage(pchar text) : Message(MessageType::ServerMessage),
    message(text)
{

}


ServerMessageMessage::~ServerMessageMessage()
{

}


void ServerMessageMessage::Compress(Compressor &data) const
{
    data << message;
}


bool ServerMessageMessage::Decompress(Decompressor &data)
{
    data >> message;

    return true;
}


bool ServerMessageMessage::HandleMessage(Player *) const
{
    TheEngine->Report(GetText());

    return true;
}


PlayerNameMessage::PlayerNameMessage(pchar _name) : Message(MessageType::PlayerName), name(_name)
{

}


void PlayerNameMessage::Compress(Compressor &data) const
{
    data << name;
}


bool PlayerNameMessage::Decompress(Decompressor &data)
{
    data >> name;

    return true;
}


MainChatMessage::MainChatMessage(pchar _text, const DateTime *_dateTime) : Message(MessageType::MainChat), text(_text)
{
    if(_dateTime)
    {
        dateTime = *_dateTime;
    }
}


void MainChatMessage::Compress(Compressor &data) const
{
    data << text;
    data << dateTime;
}


bool MainChatMessage::Decompress(Decompressor &data)
{
    data >> text;
    data >> dateTime;

    return true;
}


pchar MainChatMessage::FullText() const
{
    static String<1024> result;

    String<127> dateString;

    result = Text::Format("%s %s", dateTime.ToString(&dateString)->c_str(), text.c_str());

    return result.c_str();
}


RequestBattleMessage::RequestBattleMessage(NetworkAddress &_address) : Message(MessageType::RequestBattle), address(_address)
{
}


void RequestBattleMessage::Compress(Compressor &data) const
{
    data << address.GetAddress();
    data << address.GetPort();
}


bool RequestBattleMessage::Decompress(Decompressor &data)
{
    uint   addr = 0;
    uint16 port = 0;

    data >> addr;
    data >> port;

    address = NetworkAddress(addr, port);

    return true;
}
