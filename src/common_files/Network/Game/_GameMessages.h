#pragma once


struct Message
{
    Message(int _id) : id(_id) {}
    int id;
    VectorBuffer buffer;
};


enum CommonMessages
{
    MSG_TEXTSTRING = MSG_USER
};


enum BuildSceneMessages
{
    MSG_SCENE_REQUEST_FOR_BUILD = MSG_TEXTSTRING + 1000,
    MSG_SCENE_BUILD,
        // Vector3 - ��������� ����� ����������� �������� ������
    MSG_SCENE_LAST = MSG_SCENE_REQUEST_FOR_BUILD + 999
};


enum GameMessages
{
    MSG_KEYBOARD_KEY,
        // Key      - �������
        // bool     - ������ ��� ��������
    MSG_MOUSE_YAW,
        // int      - ��������
    MSB_MOUSE_PITCH,
        // int      - ���������
    MSG_MOUSE_KEY,
        // MouseKey
        // bool     - ������ ��� ��������
};


struct MessageRequestForBuildScene : public Message
{
    MessageRequestForBuildScene() : Message(MSG_SCENE_REQUEST_FOR_BUILD) {}
};


struct MessageBuildScene : public Message
{
    // position - ������� ��������� �������� �������
    MessageBuildScene(const Vector3 &position) : Message(MSG_SCENE_BUILD)
    {
        buffer.WriteVector3(position);
    }
};


struct MessageTextString : public Message
{
    MessageTextString(const String &message) : Message(MSG_TEXTSTRING)
    {
        buffer.WriteString(message);
    }
};
