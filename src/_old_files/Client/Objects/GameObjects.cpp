#include <stdafx.h>
#include "GameObjects.h"
#include "GameWorld.h"



GameObjectController::GameObjectController(GameObjectType gameObjType, Pi::ControllerType::S contrType) :
    RigidBodyController(contrType),
    gameObjectType(gameObjType)
{

}


GameObjectController::GameObjectController(const GameObjectController &gameObjectController) :
    RigidBodyController(gameObjectController)
{
    gameObjectType = gameObjectController.gameObjectType;
}


GameObjectController::~GameObjectController()
{

}


void GameObjectController::Preprocess()
{
    RigidBodyController::Preprocess();
}


void GameObjectController::SetDefaultParameters(const DefaultParameters *defaultParam)
{
    scaleDefault = defaultParam->scale;
    rotateDefault = defaultParam->rotate;

    Transform4D transform;
    transform.SetIdentity();
    transform.SetScale(scaleDefault, scaleDefault, scaleDefault);
    transform.SetRotationAboutX(rotateDefault.x);
    transform.SetRotationAboutY(rotateDefault.y);
    transform.SetRotationAboutZ(rotateDefault.z);
    GetTargetNode()->SetNodeTransform(transform);
}


void GameObjectController::PutOnGround(float /*gameX*/, float /*gameY*/)
{
//    Landscape *landscape = TheGameWorld->GetLandscape();

    //float z = landscape->GetHeight((int)gameX, (int)-gameY);
}
