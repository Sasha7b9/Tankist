#pragma once

using namespace Pi;

namespace Pi
{
    class VehicleController;
}


class GamePlayer : public ListElement<GamePlayer>
{
public:
    GamePlayer(PlayerKey _key, VehicleController *_controller) : key(_key), controller(_controller) { }

    PlayerKey key;
    VehicleController *controller = nullptr; //-V122
};