#pragma once


using namespace Pi;


class MainServer
{
    friend class Client;
    friend class MovementAction;

public:
    static void Create();
    static void Destroy();
    // Запрос соединения
    bool RequestConnect(pchar address, uint16 port);
    // Запрос пинга
    void RequestPing();
    // Посылает сообщение чата
    void SendChatMessage(pchar text);
    // Запрос на вход в бой.
    void RequesBattle();

private:
    MainServer();

    void SendMessage(PlayerKey key, const Message &message) const;

    void SendMessage(const Message &message) const;
};
