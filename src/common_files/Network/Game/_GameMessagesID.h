#pragma once


enum CommonMessages
{
    MSG_TEXTSTRING = MSG_USER
};


enum BuildSceneMessages
{
    MSG_REQUEST_FOR_BUILD_SCENE = MSG_TEXTSTRING + 1000,
    MSG_SCENE_BUILD,
    MSG_SCENE_LAST = MSG_REQUEST_FOR_BUILD_SCENE + 999
};


enum GameMessages
{
    MSG_KEYBOARD_KEY,
    MSG_MOUSE_YAW,
    MSB_MOUSE_PITCH,
    MSG_MOUSE_KEY
};
