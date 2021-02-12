#pragma once
#include "_GameMessagesID.h"


struct Message
{
    Message(int _id) : id(_id) {}
    void Handle(MemoryBuffer &msg);
    int id;
    VectorBuffer buffer;
};

                                                 // ������ �� ���������� �����. ����������� �������� ����� �������������
struct MessageRequestForBuildScene : public Message
{
    MessageRequestForBuildScene() : Message(MSG_SCENE_REQUEST_FOR_BUILD) {}
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
