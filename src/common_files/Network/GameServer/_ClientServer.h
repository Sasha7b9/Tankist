#pragma once


/*
*  ����� ��� ������������ � ��������
*/

class ClientServer : public Object
{
    URHO3D_OBJECT(ClientServer, Object);

public:

    ClientServer(Context *context);

    void Connect(const String &address, uint16 port);

    void SendTextMessage(const String &message);
    void SendMessage(int id);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);

    static bool IsSceneMessage(int id);
};


URHO3D_EVENT(E_SCENEMESSAGE, SceneMessage)
{
    URHO3D_PARAM(P_MESSAGEID, MessageID);
}
