/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class GameScene : public Scene
{
    URHO3D_OBJECT(GameScene, Scene);

public:

    GameScene(Context *context);
    ~GameScene();

    void Create();

public:
};
