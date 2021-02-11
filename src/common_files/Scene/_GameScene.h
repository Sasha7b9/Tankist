/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class GameScene : public Object
{
    URHO3D_OBJECT(GameScene, Object);

public:

    GameScene(Context *context);
    ~GameScene();

    void Create();

    Node *CreateChild(pchar name);

    Node *GetChild(pchar name, bool recursive = false);

    Scene *EngineScene() { return scene; };

    void SaveXML(File &file);

    void LoadXML(File &file);

    WeakPtr<Scene> scene;

public:
};
