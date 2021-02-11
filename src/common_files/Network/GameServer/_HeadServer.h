#include "defines.h"


class HeadServer : public Object
{
    URHO3D_OBJECT(HeadServer, Object);

public:

    HeadServer(Context *context);

    bool Start(uint16 port);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};