#pragma once


using namespace Pi;


class Tankist : public Application, public Singleton<Tankist>
{
public:
    Tankist();
    ~Tankist();

private:
    virtual void ApplicationTask() override;

	CommandObserver<Tankist> settingsCommandObserver;
	void HandleSettingsCommand(Command *, pchar );

    virtual void HandleConnectionEvent(ConnectionEvent::E, const NetworkAddress &, const void *) override;
};
