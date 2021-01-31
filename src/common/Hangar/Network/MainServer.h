#pragma once


class MainServer
{
public:
    static void Create();
    static void Destroy();

    bool Connect();

    int GetPing();
    int GetNumberPlayers();

private:
    MainServer();
};
