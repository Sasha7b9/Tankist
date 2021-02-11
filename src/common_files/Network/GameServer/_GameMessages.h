#pragma once


enum CommonMessages
{
    MSG_TEXTSTRING = MSG_USER
};


enum BuildSceneMessages
{
    MSG_SCENE_REQUEST_FOR_BUILD = MSG_TEXTSTRING + 1000,
    MSG_SCENE_BUILD,
        // Vector3 - положение вновь создаваемой сущности игрока
    MSG_SCENE_LAST = MSG_SCENE_REQUEST_FOR_BUILD + 999
};


//enum GameMessages
//{
//    MSG_CREATE_VEHICLE = MSG_SCENE_LAST + 1
//};
