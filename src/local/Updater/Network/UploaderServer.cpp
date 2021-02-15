// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "FileSystem/_FileSystem.h"
#include "FileSystem/_ListFiles.h"
#include "Network/UploaderServer.h"
#include "Utils/_Log.h"
#include <thread>


#define LIST_FILES                "list.txt"                        // 
#define LIST_NEW_FILES            "list_new.txt"                    // 
#define LIST_IGNORED_FILES        "list_ignored.txt"                // 
#define REMOTE_LIST_NEW_FILES     "remote_list_new_files.txt"       // Список новых файлов, подлежащих сравнению и апгрейду, если необходимо      
#define REMOTE_LIST_IGNORED_FILES "remote_list_ignored_files.txt"   // Список игнорируемых файлов - передаётся Updater-у, чтобы он их не трогал



void UploaderServer::Connect(pchar address)
{
    auto [host, port] = ConnectorTCP::ParseAddress(address);

    while (!connector.Connect(host, port))
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    connector.SetReadTimeOut(10000);
}


bool UploaderServer::UpdateFiles()
{
    FS::RemoveFile(LIST_FILES);
    FS::RemoveFile(LIST_NEW_FILES);
    FS::RemoveFile(LIST_IGNORED_FILES);

    std::vector<std::string> ignored;

    gConfig.GetVectorStrings("list ignored files", ignored);

    ListFiles allFiles(".", &ignored);

    allFiles.Write(LIST_FILES);

    connector.Transmit("get list");

    ReceiveAndWriteFile(LIST_NEW_FILES);

    connector.Transmit("get ignored list");

    ReceiveAndWriteFile(LIST_IGNORED_FILES);

    ListFiles newFiles;
    ListFiles ignoredFiles;

    newFiles.ExtractFiles(LIST_NEW_FILES);
    ignoredFiles.ExtractFiles(LIST_IGNORED_FILES);

    for (const FileInfo &info : allFiles.files)         // Сначала удаляем файлы, которых нет в новом списке
    {
        if (ignoredFiles.ExistFile(info.name))
        {
            continue;
        }

        if (!newFiles.ExistFile(info.name))
        {
            LOG_WRITE("Удаляю %s", info.name.c_str());

            FS::RemoveFile(info.name);
        }
    }

    float size = (float)newFiles.files.size();

    int counter = 1;

    for (const FileInfo &info : newFiles.files)         // А теперь перезаписываем все файлы из нового списка, которые отличаются от имеющихся
    {
        WritePercents((float)(counter++ * 100) / size);

        if (ignoredFiles.ExistFile(info.name))
        {
            continue;
        }

        if (!allFiles.ExistEqualFile(info))
        {
            std::cout << info.name << "\n";

            FS::RemoveFile(info.name);

            connector.Transmit(std::string("get file ") + info.name);

            ReceiveAndWriteFile(info.name.c_str());
        }
    }

    std::cout << '\n';

    FS::RemoveFile(LIST_FILES);
    FS::RemoveFile(LIST_NEW_FILES);
    FS::RemoveFile(LIST_IGNORED_FILES);

    return true;
}


void UploaderServer::WritePercents(float percents)
{
    float width = 74;

    for (int i = 0; i < (int)width; i++)
    {
        std::cout << (((((float)i / width) * 100.0F) < percents) ? "#" : ".");
    }

    std::cout << " " << (int)percents << " %\r";
}


void UploaderServer::ReceiveAndWriteFile(pchar fileName)
{
    std::string data = connector.ReceiveWait();

    if (data.size() == 0)
    {
        LOG_ERROR("Received file \"%s\" is empty", fileName);
    }
    else
    {
        FS::File file;
        file.Create(fileName);
        file.Write(&data[0], (int)data.size()); //-V202
    }
}

