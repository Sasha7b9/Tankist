#pragma once


/*
*  Класс для коммуникаций с сервером
*/

class ClientServer : public Object
{
    URHO3D_OBJECT(ClientServer, Object);

public:

    ClientServer(Context *context);

    void Connect(const String &address, uint16 port);

    void SendTextMessage(const String &message, bool reliable);
    void SendMessage(int id, bool reliable);
    void SendMessage(int id, const VectorBuffer &data, bool reliable);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);

    static bool IsSceneMessage(int id);
};
