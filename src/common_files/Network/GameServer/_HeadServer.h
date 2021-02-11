#include "defines.h"


class HeadServer : public GameServer
{
    URHO3D_OBJECT(HeadServer, GameServer);

public:

    HeadServer(Context *context);

    virtual bool Start(uint16 port) override;

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};