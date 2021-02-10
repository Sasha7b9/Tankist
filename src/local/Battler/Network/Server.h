#pragma once


/*
*  Класс для коммуникаций с сервером
*/

class Server : public Object
{
    URHO3D_OBJECT(Server, Object);

public:

    Server(Context *context);

    void Connect(const String &address, uint16 port);

private:

    void HandleServerConnected(StringHash, VariantMap &);
};
