#pragma once
#include "GameWorld.h"
#include "Objects/Vehicle.h"


class HangarGUI;


enum
{
    kLocatorSpectator = 'spec',
};


class Tankist : public Application, public Singleton <Tankist>
{
public:
    Tankist();
    ~Tankist();

    void SetVehicleController(VehicleController *controller)
    {
        vehicleController = controller;
    }
    VehicleController *GetVehicleController() const
    {
        return vehicleController;
    }


private:

    LocatorRegistration                 locatorReg;

    VehicleController                   *vehicleController = nullptr;
    ModelRegistration                   vehicleModelReg;
    ControllerReg<VehicleController>    controllerReg;

    HangarGUI *gui = nullptr;

    /// Взаимодействие с сервером
    CommandObserver<Tankist> serverCommandObserver;
    Command                  commandServer;
    void HandleServerCommand(Command *command, const char *text);

    static World *CreateWorld(const char *name, void *cookie);

    virtual void HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &address, const void *param) override;
    virtual void HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *param) override;
    virtual void ReceiveMessage(Player *sender, const NetworkAddress &address, const Message *message) override;
    virtual Message *CreateMessage(Pi::MessageType::E type, Decompressor& data) const override;
    virtual void HandleGameEvent(GameEvent event, const void *param) override;
    virtual void ApplicationTask() override;
    /// Послать информацию обо всех имеющихся узлах новому игроку.
    void SendInformationAboutPlayersToNewPlayer(Player *player);
    virtual Pi::EngineResult::B LoadWorld(const char *name) override;
};
