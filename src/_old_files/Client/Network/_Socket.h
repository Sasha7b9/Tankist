#pragma once
#include "cdefines.h"
#include "FileSystem.h"


class Socket
{
public:

    static const uint16 SERVER_PORT = 30001;
    static const char * const SERVER_ADDRESS;

    // Присоединиться к удалённому серверу
    bool ConnectToServer();

    // Отсоединиться от сервера
    void DisconnectFromServer();

    // Послать запрос серверу
    void SendRequest(const char *request);

    // Узнать размер файла
    int RequestFileSize(const char *nameFile);

    // Запросить файл
    void RequestFile(const char *nameFile, uint8 *buffer, int size);

    // Принять данные о файлах от удалённого сервера
    void ReceiveInfoAboutFiles(std::vector<FileInfo> &infos, const char *fileName);

private:

    uint64 my_sock = 0;

    // Принять размер от сервера
    int GetSize();

    // Разбить содержимое текстового файла на строки
    void SplitFileForStrings(const uint8 *buffer, int sizeBuffer, std::vector<std::string> &strings);
};
