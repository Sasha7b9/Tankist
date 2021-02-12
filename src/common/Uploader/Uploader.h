#pragma once
#include "Network/Other/_SocketsTCP.h"

#include <vector>
#include <string>


class Uploader
{
public:

    int Run();

private:

    // Подготовить список файлов для обновления
    void PrepareListFiles();

    int RunServer();

    // Записать список игнорируемых файлов
    void WriteListFiles(pchar name, std::vector<std::string> &ignored);
};
