#pragma once

#include "cdefines.h"

#include <cstdint>
#include <functional>
#include <thread>
#include <list>

#ifdef _WIN32

#include <WinSock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#endif


//Буфер для приёма данных от клиента
static constexpr uint16 buffer_size = 4096;


struct TcpServer
{
    class Client;
    
    //Тип Callback-функции обработчика клиента
    typedef std::function<void(Client)> FuncCallback;
    
    //Статус сервера
    enum class status : uint8
    {
        up                   = 0,
        err_socket_init      = 1,
        err_socket_bind      = 2,
        err_socket_listening = 3,
        close                = 4
    };

private:
    uint16       port;
    status       _status = status::close;
    FuncCallback handler;

    std::thread                handlerThread;
    std::list<std::thread>     clientHandlerThreads;
    std::list<std::thread::id> clientHandlingEnd;

#ifdef _WIN32
    SOCKET  servSocket = INVALID_SOCKET;
    WSAData wData;
#else
    int servSocket;
#endif

    // Функиця обработки соединений
    void HandlingLoop();

public:
    //Конструктор принимает:
    //port - порт на котором будем запускать сервер
    //handler - callback-функция, запускаямая при подключении клиента, объект которого и передают первым аргументом в callback (пример лямбда-функции: [](TcpServer::Client){...do something...})
    TcpServer(const uint16 port, FuncCallback handler) : port(port), handler(handler) {};
    ~TcpServer();

    //Задаёт callback-функцию запускаямую при подключении клиента
    void SetHandler(FuncCallback h)             { handler = h; };

    uint16_t GetPort() const                    { return port; };
    uint16_t SetPort(const uint16_t port);

    status GetStatus() const { return _status; }

    //Перезапуск сервера
    status Restart();

    //Запуск сервера
    status Start();

    //Остановка сервера
    void   Stop();

    // Вход в поток обработки соединений
    void   JoinLoop()                           {  handlerThread.join(); };
};


class TcpServer::Client
{
#ifdef _WIN32

    SOCKET      socket;
    SOCKADDR_IN address;
    char        buffer[buffer_size];

public:

    Client(SOCKET socket, SOCKADDR_IN address) : socket(socket), address(address) {}
#else

    int    socket;
    struct sockaddr_in address;
    char   buffer[buffer_size];

public:
    Client(int socket, struct sockaddr_in address) : socket(socket), address(address) {}

#endif

public:
    Client(const Client &other) : socket(other.socket), address(other.address) {}
    ~Client();

    //Загружает в буфер данные от клиента и возвращает их размер
    int   LoadData()    { return recv(socket, buffer, buffer_size, 0); };

    //Возвращает указатель на буфер с данными от клиента
    char *GetData()     { return buffer; };

    //Отправляет данные серверу
    bool  SendData(const char *buffer, const size_t size) const;

#ifdef _WIN32

    uint   GetHost() const { return address.sin_addr.S_un.S_addr; };
    uint16 GetPort() const { return address.sin_port; };

#else

    uint   GetHost() const { return address.sin_addr.s_addr; }
    uint16 GetPort() const { return address.sin_port; }

#endif
};
