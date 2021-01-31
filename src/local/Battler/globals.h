#pragma once


using namespace Pi;

class Client;
class HangarWindow;
class MainServer;
class AttemptConnectionWindow;
class NetworkWidget;
class MenuWindow;


namespace Pi
{
    class Player;
    class VehicleController;
}


extern Client                  *TheGame;
extern HangarWindow            *TheHangarWindow;
extern MainServer              *TheMainServer;
extern AttemptConnectionWindow *TheAttemptConnectionWindow;
extern NetworkWidget           *TheNetworkWidget;
extern Player                  *ThePlayer;
extern VehicleController       *TheController;
extern List<GamePlayer>         players;
extern MenuWindow              *TheMenuWindow;

extern ConfigurationFile gConfig;
extern MasterServer      gMaster;
