#include "defines.h"


Server::Server(Context *context) : Object(context)
{
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Server, HandleServerConnected));
}


void Server::Connect(const String &address, uint16 port)
{
    TheNetwork->Connect(address, port, nullptr);
}


void Server::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}
