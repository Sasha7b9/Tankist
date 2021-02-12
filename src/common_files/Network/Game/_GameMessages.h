#pragma once
#include "_GameMessagesID.h"


struct Message
{
    Message(int _id) : id(_id) {}
    void Handle(VariantMap &map);
    int id;
    VectorBuffer buffer;

#ifdef CLIENT
    void Send(bool reliable);           // ����� ������������ ������ ��� �������. ������� ����� ��� �����, � ����� ���-
                                        // ����� ��������
#endif
};


                                                                               // �� ����� ��������� ������ ������ �����
struct MessageBuildScene : public Message
{
    MessageBuildScene(
        const Vector3 &position             // ������� ��������� �������� �������
    ) :
        Message(MSG_SCENE_BUILD)
    {
        buffer.WriteVector3(position);
    }

    void Handle(MemoryBuffer &msg);
};


                                                 // ������ �� ���������� �����. ����������� �������� ����� �������������
struct MessageRequestForBuildScene : public Message
{
    MessageRequestForBuildScene() : Message(MSG_REQUEST_FOR_BUILD_SCENE) {}

    void Handle(const TConnection &connection);
};


                                                                                            // �������� ��������� ������
struct MessageTextString : public Message
{
    MessageTextString(const String &message) : Message(MSG_TEXTSTRING)
    {
        buffer.WriteString(message);
    }

    void Handle(MemoryBuffer &msg)
    {
        URHO3D_LOGINFO(msg.ReadString());
    }
};
