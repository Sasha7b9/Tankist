#pragma once


using namespace Pi;


class MainServer
{
    friend class Client;
    friend class MovementAction;

public:
    static void Create();
    static void Destroy();
    // ������ ����������
    bool RequestConnect(pchar address, uint16 port);
    // ������ �����
    void RequestPing();
    // �������� ��������� ����
    void SendChatMessage(pchar text);
    // ������ �� ���� � ���.
    void RequesBattle();

private:
    MainServer();

    void SendMessage(PlayerKey key, const Message &message) const;

    void SendMessage(const Message &message) const;
};
