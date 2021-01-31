#pragma once


using namespace Pi;


class Hangar : public Application, public Singleton<Hangar>
{
public:
    Hangar();
    ~Hangar();

private:
    bool isRunning = true;

    virtual void ApplicationTask() override;
    virtual void HandleConnectionEvent(ConnectionEvent::E, const NetworkAddress&, const void*) override;
    virtual void HandlePlayerEvent(PlayerEvent::E, Player*, const void*) override;
    virtual void HandleGameEvent(GameEvent, const void*) override;
    virtual Message* CreateMessage(MessageType::E, Decompressor&) const override;
    virtual void ReceiveMessage(Player*, const NetworkAddress&, const Message*) override;
    // Рассчёт входящего/исходящего трафика
    void CalculateTraffic(uint *speedIn, uint *speedOut);
};
