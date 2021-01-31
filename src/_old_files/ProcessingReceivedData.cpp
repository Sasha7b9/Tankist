#include "_defines.h"
#include "defines.h"
#include "Uploader.h"
#include "FileSystem/_FileSystem.h"


typedef void (*funcProcess)(sockpp::tcp_socket &sock, const std::string &command);


// Структура обработки
struct ProcessStruct
{
    std::string command;
    funcProcess func; //-V122
};


static void GetList(sockpp::tcp_socket &, const std::string &);
static void GetFile(sockpp::tcp_socket &, const std::string &);

// Обрабатывает данные из data. Возвращает количество обработанных символов
static int ProcessData(sockpp::tcp_socket &sock, const std::vector<char> &data);

// Выполнить команду command
static void RunCommand(sockpp::tcp_socket &sock, std::string &command);

// Записать в сокет данные data размером size
static void WriteToSocket(sockpp::tcp_socket &sock, const void *data, uint size);

// Передать содержимое файла
static void TransmitFile(sockpp::tcp_socket &sock, const std::string &nameFile);


static const std::vector<ProcessStruct> commands =
{
    { "get_list", GetList },
    { "get_file", GetFile }
};


void CallbackOnReceive(sockpp::tcp_socket sock)
{
    std::vector<char> buffer; //-V826

    while (sock.is_open())
    {
#define MAX_RECEIVED 512

        char received[MAX_RECEIVED];

        ssize_t n = sock.read(received, MAX_RECEIVED);       // Принимаем очередную порцию данных

        if (n <= 0)
        {
            break;
        }

        buffer.insert(buffer.end(), &received[0], &received[n]);        // Добавляем её к ранее принятым данным

        int processed = 0;

        do 
        {
            processed = ProcessData(sock, buffer);

            if (processed != 0)
            {
                buffer.erase(buffer.begin(), buffer.begin() + processed);
            }

        } while (processed != 0);
    }

    // В этой точке окажемся, когда клиент закрывает соединение

    std::cout << "closed connection" << std::endl;
}


static int ProcessData(sockpp::tcp_socket &sock, const std::vector<char> &data) //-V2506
{
    uint64 size = data.size();

    for (uint64 i = 0; i < size; i++)
    {
        if (data[i] == '\0')
        {
            std::string command;

            for (uint64 j = 0; j < i; j++)
            {
                command.push_back(data[j]);
            }

            RunCommand(sock, command);

            return static_cast<int>(i + 1);
        }
    }

    return 0;
}


static void RunCommand(sockpp::tcp_socket &sock, std::string &command)
{
    for (const ProcessStruct &str : commands)
    {
        if (command.compare(0, str.command.size(), str.command) == 0)
        {
            str.func(sock, command);
        }
    }
}


static void GetList(sockpp::tcp_socket &sock, const std::string &)
{
    TransmitFile(sock, LIST_NEW_FILES);
}


static void GetFile(sockpp::tcp_socket &sock, const std::string &command)
{
    std::string nameFile = command.substr(command.find_last_of(' ') + 1);

    TransmitFile(sock, nameFile);
}


static void TransmitFile(sockpp::tcp_socket &sock, const std::string &nameFile)
{
    FS::File file;
    file.Open(nameFile.c_str());

    uint size = file.Size();

    std::vector<char> data((size_t)size); //-V201

    file.Read(&data[0], (int)size);

    WriteToSocket(sock, &data[0], static_cast<uint>(size));
}


static void WriteToSocket(sockpp::tcp_socket &sock, const void *data, uint size)
{
    sock.write_n(&size, sizeof(uint));

    sock.write_n(data, (size_t)size); //-V2533 //-V201
}
