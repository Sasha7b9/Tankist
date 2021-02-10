#include "defines.h"


class Server : public Object
{
    URHO3D_OBJECT(Server, Object);

public:

    Server(Context *context);

    bool Start(uint16 port);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};