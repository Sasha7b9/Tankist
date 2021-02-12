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

    void SendMessage(int id, bool reliable, const DataNetwork &data);

    void SendTextMessage(const String &message, bool reliable);
    void SendMessage(int id, bool reliable);
    //void SendMessage(int id, const VectorBuffer &data, bool reliable);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);

    static bool IsSceneMessage(int id);
};
