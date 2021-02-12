#pragma once
#include "FileSystem/_ConfigurationFile.h"
#include "Network/Other/_MasterServer.h"

class Chat;
class Hangar;
class MainServer;

extern Hangar *TheGame;
extern Chat *TheChat;
extern MainServer *TheMainServer;


extern MasterServer      gMaster;
extern ConfigurationFile gConfig;

