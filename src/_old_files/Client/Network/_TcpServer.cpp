#include "Network/cTcpServer.h"
#include <chrono>


//Деструктор останавливает сервер если он был запущен и вычищает заданную версию WinSocket
TcpServer::~TcpServer()
{
    if (_status == status::up)
    {
        Stop();
    }

#ifdef _WIN32

    WSACleanup();

#endif
}


uint16_t TcpServer::SetPort(const uint16_t p)
{
    port = p;
    Restart();
    return port;
}


TcpServer::status TcpServer::Restart()
{
    if (_status == status::up)
    {
        Stop();
    }

    return Start();
}


bool TcpServer::Client::SendData(const char *buf, const size_t size) const
{
    if (send(socket, buf, static_cast<int>(size), 0) < 0)
    {
        return false;
    }

    return true;
}


#ifdef _WIN32
TcpServer::status TcpServer::Start()
{
    WSAStartup(MAKEWORD(2, 2), &wData); //Задаём версию WinSocket

    SOCKADDR_IN address;                        //Структура хост/порт/протокол для инициализации сокета
    address.sin_addr.S_un.S_addr = INADDR_ANY;  //Любой IP адресс
    address.sin_port = htons(port);             //Задаём порт
    address.sin_family = AF_INET;               //AF_INET - Cемейство адресов для IPv4

    //Инициализируем наш сокет и проверяем корректно ли прошла инициализация
    //в противном случае возвращаем статус с ошибкой
    if (static_cast<int>(servSocket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
        return _status = status::err_socket_init;
    }

    //Присваиваем к сокету адресс и порт и проверяем на коректность сокет
    //в противном случае возвращаем статус с ошибкой
    if (bind(servSocket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
    {
        return _status = status::err_socket_bind;
    }

    //Запускаем прослушку и проверяем запустилась ли она
    //в противном случае возвращаем статус с ошибкой
    if (listen(servSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        return _status = status::err_socket_listening;
    }

    //Меняем статус, запускаем обработчик соединений и возвращаем статус
    _status = status::up;
    handlerThread = std::thread([this] {HandlingLoop(); });

    return _status;
}


void TcpServer::Stop()
{
    _status = status::close;        //Изменение статуса
    closesocket(servSocket);        //Закрытие сокета
    JoinLoop();                     //Ожидание завершения

    for (std::thread &cl_thr : clientHandlerThreads) //Перебор всех клиентских потоков
    {
        cl_thr.join();              // Ожидание их завершения
    }

    clientHandlerThreads.clear();   // Очистка списка клиентских потоков
    clientHandlingEnd.clear();      // Очистка списка идентификаторов завершённых клиентских потоков
}


void TcpServer::HandlingLoop()
{
    while (_status == status::up)
    {
        SOCKET client_socket;               //Сокет клиента
        SOCKADDR_IN client_addr;            //Адресс клиента
        int addrlen = sizeof(client_addr);  //Размер адреса клиента

        //Получение сокета и адреса клиента (если сокет коректен и сервер зарущен запуск потока обработки)
        if ((client_socket = accept(servSocket, (struct sockaddr *)&client_addr, &addrlen)) != 0 && _status == status::up)
        {
            clientHandlerThreads.push_back(std::thread([this, &client_socket, &client_addr]
                {
                    handler(Client(client_socket, client_addr));                //Запуск callback-обработчика
                    clientHandlingEnd.push_back(std::this_thread::get_id());    //Добавление идентификатора в список идентификаторов завершённых клиентских потоков
                }));
        }

        //Очистка отработанных клиентских потоков
        if (!clientHandlingEnd.empty())
        {
            for (std::list<std::thread::id>::iterator id_it = clientHandlingEnd.begin(); !clientHandlingEnd.empty(); id_it = clientHandlingEnd.begin())
            {
                for (std::list<std::thread>::iterator thr_it = clientHandlerThreads.begin(); thr_it != clientHandlerThreads.end(); ++thr_it)
                {
                    if (thr_it->get_id() == *id_it)
                    {
                        thr_it->join();
                        clientHandlerThreads.erase(thr_it);
                        clientHandlingEnd.erase(id_it);
                        break;
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


TcpServer::Client::~Client()
{
    shutdown(socket, 0);    //Обрыв соединения сокета
    closesocket(socket);    //Закрытие сокета
}


#else

//Запуск сервера (по аналогии с реализацией для Windows)
TcpServer::status TcpServer::Start()
{
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (servSocket == -1)
    {
        return _status = status::err_socket_init;
    }

    if (bind(servSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return _status = status::err_socket_bind;
    }

    if (listen(servSocket, 3) < 0)
    {
        return _status = status::err_socket_listening;
    }

    _status = status::up;
    handler_thread = std::thread([this] { HandlingLoop(); });

    return _status;
}


void TcpServer::Stop()
{
    _status = status::close;
    close(servSocket);
    JoinLoop();

    for (std::thread &cl_thr : client_handler_threads)
    {
        cl_thr.join();
    }

    client_handler_threads.clear();
    client_handling_end.clear();
}


// Функиця обработки соединений (по аналогии с реализацией для Windows)
void TcpServer::HandlingLoop()
{
    while (_status == status::up)
    {
        int client_socket;
        struct sockaddr_in client_addr;
        int addrlen = sizeof(struct sockaddr_in);
        if ((client_socket = accept(servSocket, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) >= 0 && _status == status::up)
        {
            client_handler_threads.push_back(std::thread([this, &client_socket, &client_addr]
                {
                    handler(Client(client_socket, client_addr));
                    client_handling_end.push_back(std::this_thread::get_id());
                }));
        }

        if (!client_handling_end.empty())
        {
            for (std::list<std::thread::id>::iterator id_it = client_handling_end.begin(); !client_handling_end.empty(); id_it = client_handling_end.begin())
            {
                for (std::list<std::thread>::iterator thr_it = client_handler_threads.begin(); thr_it != client_handler_threads.end(); ++thr_it)
                {
                    if (thr_it->get_id() == *id_it)
                    {
                        thr_it->join();
                        client_handler_threads.erase(thr_it);
                        client_handling_end.erase(id_it);
                        break;
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


// Конструктор копирования
TcpServer::Client::Client(const TcpServer::Client &other) : socket(other.socket), address(other.address) {}

TcpServer::Client::~Client()
{
    shutdown(socket, 0); //Обрыв соединения сокета
    close(socket); //Закрытие сокета
}

#endif
