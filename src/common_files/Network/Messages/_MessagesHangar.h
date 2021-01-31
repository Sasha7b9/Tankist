#pragma once


using namespace Pi;


namespace Pi
{
    namespace MessageType
    {
        enum : E
        {
            ServerKill = BaseCount,     ///< Остановить сервер
            ServerMessage,              ///< Текстовое сообщение от сервера
            PlayerName,                 ///< Сообщение об имени игрока
            MainChat,                   ///< Сообщение от сервера в главный чат
            RequestBattle,              ///< Запрос на вход в бой
            MessageHangarCount
        };
    }
}


/// Это сообщение посылаем, чтобы прекратить выполнение сервера
class ServerKillMessage : public Message
{
    friend class Client;

public:
    ServerKillMessage();
    virtual ~ServerKillMessage();

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;
};


/// Текстовое сообщение от сервера
class ServerMessageMessage : public Message
{
public:
    ServerMessageMessage();
    ServerMessageMessage(pchar text);
    virtual ~ServerMessageMessage();

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

    pchar GetText() const { return message.c_str(); }

    virtual bool HandleMessage(Player *sender) const override;

private:
    PiString message;
};


/// Посылается серверу после подключения чтобы сообщить своё имя
class PlayerNameMessage : public Message
{
public:
    PlayerNameMessage(pchar name = "");

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

    pchar GetName() const { return name.c_str(); }

private:
    PiString name;
};


class MainChatMessage : public Message
{
public:
    MainChatMessage(pchar text = "", const DateTime *dataTime = nullptr);

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

    pchar FullText() const;

    PiString text;
private:
    DateTime dateTime;
};


class RequestBattleMessage : public Message
{
public:
    RequestBattleMessage() : Message(MessageType::RequestBattle) {}
    RequestBattleMessage(NetworkAddress &address);

    virtual void Compress(Compressor &) const override;
    virtual bool Decompress(Decompressor &) override;

    NetworkAddress address;
};
