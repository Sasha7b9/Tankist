#pragma once


using namespace Pi;

namespace Pi
{
    class VehicleController;
    class UseAction;
}


class RespawnDoMessage;
class MovementAction;


class Client : public Application, public Singleton<Client>
{
public:
    Client();
    ~Client();

    CommandObserver<Client> serverCommandObserver;
    void HandleServerCommand(Command *, pchar );

    VehicleController *GetVehicleController(void) const
    {
        return (vehicleController);
    }

    void SetVehicleController(VehicleController *controller)
    {
        vehicleController = controller;
    }

    EngineResult::B LoadWorld(pchar name);

    void AcceptActions();

private:

    MovementAction *forwardAction = nullptr; //-V122
    MovementAction *backwardAction; //-V122
    MovementAction *leftAction; //-V122
    MovementAction *rightAction; //-V122
    MovementAction *upAction; //-V122
    MovementAction *downAction; //-V122

    DisplayEventHandler	                displayEventHandler;

    VehicleController                   *vehicleController; //-V122

    ModelRegistration                   vehicleModelReg;
    ControllerReg<VehicleController>	controllerReg;

    LocatorRegistration				    locatorReg;

    InputMgr::KeyProc *prevEscapeProc; //-V122
    void *prevEscapeCookie; //-V122

    UseAction *useAction; //-V122

    static World *ConstructWorld(pchar name, void *data);

    static void HandleDisplayEvent(const DisplayEventData *eventData, void *data);

    static void EscapeProc(void *data);

    void UnloadWorld(void);

    virtual void ApplicationTask() override;

    virtual void HandleConnectionEvent(ConnectionEvent::E, const NetworkAddress &, const void *) override;

    virtual Message *CreateMessage(MessageType::E, Decompressor &) const override;

    virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;

    virtual void HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *param) override;

    virtual void HandleGameEvent(GameEvent event, const void *param) override;
    // Обработка сообщения о репликации
    void CreatePlayer(const RespawnDoMessage *message);
};
