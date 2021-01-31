#pragma once


typedef Pi::Type GameObjectType;



class DefaultParameters
{

public:

    DefaultParameters(float s, const Vector3D &rot) :
        scale(s),
        rotate(rot)
    {

    }

    float scale = 1.0f;
    Vector3D rotate;
};



class GameObjectController : public RigidBodyController, public LinkTarget < GameObjectController >
{

public:

    virtual ~GameObjectController();

    void Preprocess() override;

    void SetDefaultParameters(const DefaultParameters *defaultParam);
    void PutOnGround(float gameX, float gameY);

protected:

    GameObjectController(GameObjectType gameObjType, Pi::ControllerType::S contrType);
    GameObjectController(const GameObjectController &gameObjectController);

private:

    GameObjectType gameObjectType;

    float scaleDefault = 1.0F;
    Vector3D rotateDefault;


    Point3D coordGame;
};
