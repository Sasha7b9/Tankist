#pragma once
#include "_GameMessagesID.h"


namespace Message
{

    struct GameMessage
    {
        GameMessage(int _id) : id(_id) {}
        void Handle(VariantMap &map);
        int id;
        VectorBuffer buffer;

#ifdef CLIENT
        void Send(bool reliable);           // ����� ������������ ������ ��� �������. ������� ����� ��� �����, � ����� ���-
                                            // ����� ��������
#endif
    };


    // �� ����� ��������� ������ ������ �����
    struct BuildScene : public GameMessage
    {
        BuildScene(const Vector3 &position)             // ������� ��������� �������� �������
            : GameMessage(MSG_BUILD_SCENE)
        {
            buffer.WriteVector3(position);
        }

        void Handle(MemoryBuffer &msg);
    };


    // ������ �� ���������� �����. ����������� �������� ����� �������������
    struct RequestForBuildScene : public GameMessage
    {
        RequestForBuildScene() : GameMessage(MSG_REQUEST_FOR_BUILD_SCENE) {}

        void Handle(const TConnection &connection);
    };


    // �������� ��������� ������
    struct TextString : public GameMessage
    {
        TextString(const String &message) : GameMessage(MSG_TEXTSTRING)
        {
            buffer.WriteString(message);
        }

        void Handle(MemoryBuffer &msg)
        {
            URHO3D_LOGINFO(msg.ReadString());
        }
    };


    // �������/���������� ������
    struct KeyEvent : public GameMessage
    {
        KeyEvent(Key key,                                       // ��� �������
            bool press) : GameMessage(MSG_KEY_EVENT)            // true - �������, false, ����������
        {
            buffer.WriteInt(key);
            buffer.WriteBool(press);
        }

        void Handle(MemoryBuffer &msg)
        {
            int key = msg.ReadInt();
            String press(msg.ReadBool() ? "press" : "leave");
            URHO3D_LOGINFOF("Key : %d, %s", key, press.CString());
        }
    };

}
