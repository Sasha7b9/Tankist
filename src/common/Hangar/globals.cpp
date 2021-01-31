#include <stdafx.h>
#include "globals.h"
#include "Chat.h"
#include "Hangar.h"
#include "Network/MainServer.h"


Hangar *TheGame = nullptr;
Chat *TheChat = nullptr;
MainServer *TheMainServer = nullptr;


MasterServer gMaster;
ConfigurationFile gConfig;
