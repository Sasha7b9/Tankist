#pragma once


class GameScene : public Object
{
    URHO3D_OBJECT(GameScene, Object);

public:

    GameScene(Context *context) : Object(context) {}

    void Create();
};
