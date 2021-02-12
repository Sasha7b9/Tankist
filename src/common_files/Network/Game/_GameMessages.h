#pragma once
#include "_GameMessagesID.h"


namespace Message
{

    struct Message
    {
        Message(int _id) : id(_id) {}
        void Handle(VariantMap &map);
        int id;
        VectorBuffer buffer;

        void Send(bool reliable);           // ����� ������������ ������ ��� �������. ������� ����� ��� �����, � ����� ���-
                                            // ����� ��������
    };


    // �� ����� ��������� ������ ������ �����
    struct BuildScene : public Message
    {
        BuildScene(const Vector3 &position)             // ������� ��������� �������� �������
            : Message(MSG_BUILD_SCENE)
        {
            buffer.WriteVector3(position);
        }

        void Handle(MemoryBuffer &msg);
    };


    // ������ �� ���������� �����. ����������� �������� ����� �������������
    struct RequestForBuildScene : public Message
    {
        RequestForBuildScene() : Message(MSG_REQUEST_FOR_BUILD_SCENE) {}

        void Handle(const TConnection &connection);
    };


    // �������� ��������� ������
    struct TextString : public Message
    {
        TextString(const String &message) : Message(MSG_TEXTSTRING)
        {
            buffer.WriteString(message);
        }

        void Handle(MemoryBuffer &msg)
        {
            URHO3D_LOGINFO(msg.ReadString());
        }
    };


    // �������/���������� ������
    struct KeyEvent : public Message
    {
        KeyEvent(Key key,                                       // ��� �������
            bool press) : Message(MSG_KEY_EVENT)                // true - �������, false, ����������
        {
            buffer.WriteInt(key);
            buffer.WriteBool(press);
        }

        void Handle(MemoryBuffer &msg);
    };

}
