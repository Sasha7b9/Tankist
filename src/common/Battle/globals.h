#pragma once


class GamePlayer;
class Server;

namespace Pi
{
    class Gizmo;
    template <class type> class List;
}

extern Server *TheGame;
extern Pi::Gizmo *TheGizmo;
extern Pi::List<GamePlayer> players;


extern MasterServer      gMaster;
extern ConfigurationFile gConfig;

