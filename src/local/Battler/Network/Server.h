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

    void SendMessage(const String &message);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};
