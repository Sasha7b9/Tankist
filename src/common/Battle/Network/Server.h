#include "defines.h"


class Server : public Object
{
    URHO3D_OBJECT(Server, Object);

public:
    Server(Context *context);

    bool Start(uint16 port);
private:
};