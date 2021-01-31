#include <stdafx.h>
#include "MainServer.h"


MainServer::MainServer()
{

}


void MainServer::Create()
{
    TheMainServer = new MainServer(); //-V2511
}


void MainServer::Destroy()
{
    delete TheMainServer; //-V2511
}


bool MainServer::Connect()
{
    return false;
}


int MainServer::GetPing()
{
    return -1;
}


int MainServer::GetNumberPlayers()
{
    return -1;
}
