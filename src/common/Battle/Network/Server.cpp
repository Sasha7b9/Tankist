#include "stdafx.h"


bool Server::Start(uint16 port)
{
    return TheNetwork->StartServer(port);
}
