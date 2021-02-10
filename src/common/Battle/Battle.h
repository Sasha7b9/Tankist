#pragma once


class Battle : public Application
{
    URHO3D_OBJECT(Battle, Application);

public:

    explicit Battle(Context *context);

    virtual void Start() override;

    virtual void Setup() override;

    virtual void Stop() override;

private:

    void SubscribeToEvents();

    void HandleNetworkMessage(StringHash, VariantMap &);

    void HandleConnectionStatus(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);
};