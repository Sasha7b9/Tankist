#pragma once


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
