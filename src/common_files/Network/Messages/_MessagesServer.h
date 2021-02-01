#pragma once


using namespace  Pi;


namespace Pi
{
    namespace MessageType
    {
        enum : E
        {
            Movement = MessageHangarCount,  ///< Управление
            ServerInfo,                     ///< Рассылка сервером серверной информации
            RemovePlayer,                   ///< После отключения игрока от сервера тот должен разослать оставшимся игрокам информацию об этом
            RespawnRequest,                 ///< Запрос возрождение
            RespawnDo,                      ///< Иноформация о возрождении
            TankInfo,                       ///< Используется для передачи клиентам информации о других игроках
            ServerPing                      ///< Запрос пинга
        };
    }
}


class RespawnRequestMessage : public Message
{
    friend class Client;
    friend class Server;

public:

    virtual void Compress(Compressor &) const override { };
    virtual bool Decompress(Decompressor &) override   { return true; };

private:
    RespawnRequestMessage() : Message(MessageType::RespawnRequest) { };
};


class RemovePlayerMessage : public Message
{
    friend class Client;
public:
    RemovePlayerMessage(PlayerKey _key) : Message(MessageType::RemovePlayer), key(_key) { }
    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;
private:
    RemovePlayerMessage() : Message(MessageType::RemovePlayer) { }
    PlayerKey key = 0;
};


class RespawnDoMessage : public Message
{
    friend class Client;
    friend class Server;

public:
    RespawnDoMessage(PlayerKey key, Point3D position, int index);

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

private:
    RespawnDoMessage();

    Point3D position;
    int index = 0;
    PlayerKey key = 0;
};


class MovementMessage : public Message
{
    friend class Server;
    friend class Client;

public:
    MovementMessage(uint direction, bool begin);
    ~MovementMessage();

    virtual void Compress(Compressor& data) const override;
    virtual bool Decompress(Decompressor &data) override;

private:
    MovementMessage();

    uint direction = 0;
    bool begin = true;
};


/// Запрос пинга
class ServerPingMessage : public Message
{
public:
    ServerPingMessage();

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

    int GetPing() const;

    uint NumberMessage() const
    {
        return numberMessage;
    }

private:
    // Время посылки сообщения
    uint timeSend = 0;

    static uint lastMessage;
    uint numberMessage = 0;
};


class MessageTankInfo : public Pi::Message
{
public:
    MessageTankInfo(Point3D position, String<> nameNode, bool create);
    ~MessageTankInfo();

    virtual void Compress(Compressor& data) const override;
    virtual bool Decompress(Decompressor &data);

    virtual bool HandleMessage(Player *sender) const override;

private:
    MessageTankInfo();

    Point3D position;
    String<> nameNode;
    bool create = false;    ///< true означает, что передаётся информация о новом узле, который нужно создать и вставить в сцену
};


class ServerInfoMessage : public Message
{
public:
    ServerInfoMessage(uint *speedIn = nullptr, uint *speedOut = nullptr);

    virtual void Compress(Compressor &data) const override;
    virtual bool Decompress(Decompressor &data) override;

    int count;          // Количество игроков на сервере
    int fps;            // FPS сервера
    uint sendedBytes;   // Принято байт всего
    uint receivedBytes; // Передано байт всего
    uint speedIn;       // Принято байт в секунду
    uint speedOut;      // Передано байт в секунду
};
