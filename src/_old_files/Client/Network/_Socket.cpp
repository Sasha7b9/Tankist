#include <Windows.h>
#include "Network/cSocket.h"
#include <cstring>
#include <iostream>


const char *const Socket::SERVER_ADDRESS = "78.24.217.211";


bool Socket::ConnectToServer()
{
    WSADATA data;
    HOSTENT *hst;
    sockaddr_in dest_addr;

    if (WSAStartup(MAKEWORD(2, 0), &data) == 0)                     // »нициализаци€ библиотеки WinSock
    {
        my_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (my_sock != INVALID_SOCKET)
        {
            dest_addr.sin_family = AF_INET;
            dest_addr.sin_port = htons(SERVER_PORT);

            if (inet_addr(SERVER_ADDRESS) != INADDR_NONE)           // ѕреобразование IP адреса из символьного в сетевой формат
            {
                dest_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
            }
            else
            {
                hst = gethostbyname(SERVER_ADDRESS);                // ѕопытка получить IP адрес 
                if (hst)
                {
                    // hst->h_addr_list содержит не массив адресов, а массив указателей на адреса
                    reinterpret_cast<unsigned long *>(&dest_addr.sin_addr)[0] = reinterpret_cast<unsigned long **>(hst->h_addr_list)[0][0];
                }
            }
        }
    }


    if (connect(my_sock, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
    {
        DisconnectFromServer();
        return false;
    }

    return true;
}


void Socket::DisconnectFromServer()
{
    closesocket(my_sock);
    WSACleanup();
}


void Socket::SendRequest(const char *request)
{
    send(my_sock, request, (int)std::strlen(request), 0);
}


int Socket::RequestFileSize(const char *nameFile)
{
    char request[200];

    std::snprintf(request, 199, "get_file_size %s", nameFile);

    SendRequest(request);

    int size = GetSize();

    if (size == 0)
    {
        std::cout << "file " << nameFile << " have a zero size" << std::endl;
    }

    return size;
}


void Socket::RequestFile(const char *nameFile, uint8 *buffer, int size)
{
    char request[200];

    snprintf(request, 199, "get_file %s", nameFile);

    SendRequest(request);

    int allRecieved = 0;

    while (allRecieved < size)
    {
        allRecieved += recv(my_sock, (char *)(buffer + allRecieved), size - allRecieved, 0);
    }
}


int Socket::GetSize()
{
    char buffer[100];

    int numBytes = recv(my_sock, buffer, 100, 0);

    buffer[numBytes] = 0;

    return atoi(buffer);
}


void Socket::ReceiveInfoAboutFiles(std::vector<FileInfo> &infos, const char *fileName)
{
    int sizeFilesList = RequestFileSize("files_new.txt");

    uint8 *buffer = new uint8[sizeFilesList];

    RequestFile(fileName, buffer, sizeFilesList);

    std::vector<std::string> strings;

    SplitFileForStrings(buffer, sizeFilesList, strings);

    for (int numString = 0; numString < strings.size(); numString++)
    {
        std::string str = strings[numString];

        FileInfo info;

        int start = 0;
        int end = 0;

        for (int i = start; i < str.size(); i++)
        {
            if (str[i] == ' ')
            {
                for (int pos = start; pos < end; pos++)
                {
                    info.name.push_back(str[pos]);
                }

                start = i + 1;
                end = start;

                break;
            }
            end++;
        }

        for (int i = start; i < str.size(); i++)
        {
            if (str[i] == ' ')
            {
                std::string strSize;

                for (int pos = start; pos < end; pos++)
                {
                    strSize.push_back(str[pos]);
                }

                info.size = atoi(strSize.c_str());

                start = i + 1;
                end = start;

                break;
            }
            end++;
        }

        std::string strCrc;

        for (int pos = start; pos < str.size(); pos++)
        {
            strCrc.push_back(str[pos]);
        }

        info.crc = static_cast<uint>(atoll(strCrc.c_str()));

        infos.push_back(info);
    }

    delete[]buffer;
}


void Socket::SplitFileForStrings(const uint8 *buffer, int sizeBuffer, std::vector<std::string> &strings)
{
    std::string str;

    for (int i = 0; i < sizeBuffer; i++)
    {
        if (buffer[i] == '\r' || buffer[i] == '\n')
        {
            str.push_back('\0');

            strings.push_back(str);

            str.clear();
        }
        else
        {
            str.push_back(buffer[i]);
        }
    }
}
