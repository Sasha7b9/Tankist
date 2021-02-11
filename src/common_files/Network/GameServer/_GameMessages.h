#pragma once


enum CommonMessages
{
    MSG_TEXTSTRING = MSG_USER
};


enum BuildSceneMessages
{
    MSG_SCENE_REQUEST_FOR_BUILD = MSG_TEXTSTRING + 1000,
    MSG_SCENE_CREATE_OCTREE,                            // scene->CreateComponent<Octree>()
    MSG_SCENE_CREATE_PHYSICS_WORLD                      // scene->CreateComponent<PhysicsWorld>()
};
