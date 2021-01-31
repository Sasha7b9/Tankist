#pragma once


using namespace Pi;


class RespawnDoMessage;


class Server : public Application, public Singleton<Server>
{
public:
    Server();
    ~Server();

    EngineResult::B LoadWorld(pchar name);

private:

    ModelRegistration                   vehicleModelReg;
    ControllerReg<VehicleController>	controllerReg;

    LocatorRegistration				    locatorReg;

    static World *ConstructWorld(pchar name, void *data);

    void UnloadWorld(void);

    virtual void ApplicationTask() override;

    virtual void HandleConnectionEvent(ConnectionEvent::E, const NetworkAddress &, const void *) override;

    virtual Message *CreateMessage(MessageType::E, Decompressor &) const override;

    virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;

    virtual void HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *param) override;

    virtual void HandleGameEvent(GameEvent event, const void *param) override;
    // При присоединении нового игрока нужно вызывать эту функцию
    void CreateNewPlayer(const RespawnDoMessage *message);
    // Расчёт входящего/исходящего трафика
    void CalculateTraffic(uint *speedIn, uint *speedOut);
};
