// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "FileSystem/_FileSystem.h"
#include "Network/Other/_SocketsTCP.h"


class UploaderServer
{
public:

    void Connect(pchar address);

    bool UpdateFiles();

private:

    ConnectorTCP connector;

    void ReceiveAndWriteFile(pchar fileName);

    void WritePercents(float percents);
};
