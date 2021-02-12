#include "stdafx.h"
#include "defines.h"
#include "globals.h"
#include "Uploader.h"
#include "FileSystem/_ConfigurationFile.h"
#include "FileSystem/_FileSystem.h"
#include "FileSystem/_ListFiles.h"
#include "Network/Other/_MasterServer.h"
#include "Network/Other/_SocketsTCP.h"
#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"

#include <thread>


/*
    - Построить список файлов.
    - Считать из файла конфигурации адрес мастер-сервера.
    - Подключиться к мастер-серверу.
    - Узнать у него, к какому порту подключиться - "get address uploader"
    - Прибиндиться к нужному порту
    - Обрабатывать команды:
        "get ignored list" - получить список запрещённых файлов
        "get list" - получить список файлов, подлежащих обновлению
        "get file" - получить файл
*/


// Список новых файлов, подлежащих сравнению и апгрейду, если необходимо
#define LIST_NEW_FILES          "remote_list_new_files.txt"

// Список игнорируемых файлов - передаётся Updater-у, чтобы он их не трогал
#define LIST_IGNORED_FILES      "remote_list_ignored_files.txt"


static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size);


int Uploader::Run() //-V2504
{
    PrepareListFiles();

    return RunServer();
}


void Uploader::PrepareListFiles()
{
    LOG_WRITE("Prepare list files ...");

    FS::RemoveFile(LIST_NEW_FILES);
    FS::RemoveFile(LIST_IGNORED_FILES);

    std::vector<std::string> ignoredFiles;
    std::vector<std::string> ignoredExtensions;

    gConfig.GetVectorStrings("list ignored files", ignoredFiles);
    gConfig.GetVectorStrings("list ignored extensions", ignoredExtensions);

    ListFiles allFiles(".", &ignoredFiles, &ignoredExtensions);

    allFiles.Write(LIST_NEW_FILES);

    WriteListFiles(LIST_IGNORED_FILES, ignoredFiles);

    LOG_WRITE("... done");
}


void Uploader::WriteListFiles(pchar name, std::vector<std::string> &ignored)
{
    FS::File file;
    file.Create(name);

    for (std::string &it : ignored)
    {
        file << it.c_str() << "\r\n";
    }
}


int Uploader::RunServer()
{
    gMaster.Connnect();

    auto selfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_UPLOADER);

    gMaster.Destroy();

    uint16 port = ConnectorTCP::ParseAddress(selfAddress.c_str()).second;

    AcceptorTCP acceptor;

    if (acceptor.Bind(port))
    {
        LOG_WRITE("Wait connections ...");

        while (true)
        {
            AcceptorTCP::Socket socket;

            if (acceptor.Accept(socket))
            {
                socket.Run(HandlerReceivedSocket);
            }
            else
            {
                LOG_ERROR("Error accept");
            }
        }
    }

    return 0;
}


static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size)
{
#define GET_LIST         "get list"
#define GET_IGNORED_LIST "get ignored list"

    static std::string buffer;

    buffer.append(data, (size_t)size); //-V201

    if (buffer.size() < 5)
    {
        return;
    }

    uint *sizeCommand = (uint *)&buffer[0]; //-V206

    if (buffer.size() - sizeof(uint) < *sizeCommand) //-V104
    {
        return;
    }

    std::vector<std::string> words;

    SU::SplitToWords(&buffer[sizeof(uint)], (int)*sizeCommand, words);

    if (words[0] == "get" && words[1] == "list")
    {
        FS::File file;
        file.Open(LIST_NEW_FILES, __FILE__, __LINE__);

        std::string trans;
        trans.resize((size_t)(file.Size())); //-V201

        file.Read(&trans[0], file.Size());

        socket.Transmit(trans);
    }
    else if (words[0] == "get" && words[1] == "ignored" && words[2] == "list")
    {
        FS::File file;
        file.Open(LIST_IGNORED_FILES, __FILE__, __LINE__);

        std::string trans;
        trans.resize(file.Size()); //-V106

        file.Read(&trans[0], file.Size());

        socket.Transmit(trans);
    }
    else if (words[0] == "get" && words[1] == "file") //-V2516
    {
        FS::File file;

        std::string fileName(words[2]);

#ifdef WIN32
#else
        SU::ReplaceSymbols(fileName, '\\', '/');
#endif

        file.Open(fileName.c_str(), __FILE__, __LINE__);

        std::string trans;
        trans.resize(file.Size()); //-V106

        file.Read(&trans[0], file.Size());

        socket.Transmit(trans);
    }

    buffer.erase(0, sizeof(uint) + *sizeCommand); //-V104
}
