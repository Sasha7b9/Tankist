#include <stdafx.h>


using namespace Pi;


Client                  *TheGame = nullptr;
HangarWindow            *TheHangarWindow = nullptr;
MainServer              *TheMainServer = nullptr;
AttemptConnectionWindow *TheAttemptConnectionWindow = nullptr;
NetworkWidget           *TheNetworkWidget = nullptr;
Player                  *ThePlayer = nullptr;
VehicleController       *TheController = nullptr;
List<GamePlayer>         players;
MenuWindow              *TheMenuWindow = nullptr;

ConfigurationFile gConfig;
MasterServer      gMaster;
