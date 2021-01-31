#include <stdafx.h>
#include "Input.h"
#include "GameWorld.h"
#include "globals.h"
#include "Network/Messages.h"



static CameraAction* forwardAction = nullptr;
static CameraAction* backwardAction = nullptr;
static CameraAction* leftAction = nullptr;
static CameraAction* rightAction = nullptr;
static CameraAction* upAction = nullptr;
static CameraAction* downAction = nullptr;

static TankAction* tankForward = nullptr;
static TankAction* tankBackward = nullptr;
static TankAction* tankLeft = nullptr;
static TankAction* tankRigh = nullptr;

static TankAction* rotateTowerLeft = nullptr;
static TankAction* rotateTowerRight = nullptr;



CameraAction::CameraAction(uint type, uint flag) : Action(type)
{
    movementFlag = flag;
}


CameraAction::~CameraAction()
{

}


void CameraAction::Begin()
{
    /*
    GameWorld *world = static_cast<GameWorld *>(TheWorldMgr->GetWorld());
    if (world)
    {
        SpectatorCamera *camera = world->GetCamera();
        camera->SetSpectatorFlags(camera->GetSpectatorFlags() | movementFlag);
    }
    */
}


void CameraAction::End()
{
    /*
    GameWorld *world = static_cast<GameWorld *>(TheWorldMgr->GetWorld());
    if (world)
    {
        SpectatorCamera *camera = world->GetCamera();
        camera->SetSpectatorFlags(camera->GetSpectatorFlags() & ~movementFlag);
    }
    */
}


TankAction::TankAction(uint type, uint flag) : Action(type), movementFlag(flag)
{
}


TankAction::~TankAction()
{

}


void TankAction::Begin()
{
    if (PiHEADLESS)
    {

    }
    else
    {
        TheMessageMgr->SendMessage(Pi::PlayerType::Server, MessageMovement(movementFlag));
    }
//    else if (PiSINGLE)
//    {
//        VehicleController *vehicleController = TheGame->GetVehicleController();
//
//        if (vehicleController)
//        {
//            vehicleController->SetMovementFlags(vehicleController->GetMovementFlags() | movementFlag);
//        }
//
//        /*
//        if (TheTank)
//        {
//            TheTank->GetController()->AddMovementFlag(movementFlag);
//        }
//        */
//    }
}


void TankAction::End()
{
    if (PiHEADLESS)
    {

    }
    else
    {
        TheMessageMgr->SendMessage(Pi::PlayerType::Server, MessageMovement(movementFlag | (1 << 31)));
    }
//    else if (PiSINGLE)
//    {
//        VehicleController *vehicleController = TheGame->GetVehicleController();
//        if (vehicleController)
//        {
//            vehicleController->SetMovementFlags(vehicleController->GetMovementFlags() & ~movementFlag);
//        }
//
//        /*
//        if (TheTank)
//        {
//            TheTank->GetController()->RemoveMovementFlag(movementFlag);
//        }
//        */
//    }
}


void Input::Construct()
{
    if(PiHEADLESS)
    {
        return;
    }

    forwardAction  = new CameraAction(ActionType::CameraForward, Pi::SpectatorFlag::MoveForward);
    backwardAction = new CameraAction(ActionType::CameraBackward, Pi::SpectatorFlag::MoveBackward);
    leftAction     = new CameraAction(ActionType::CameraLeft, Pi::SpectatorFlag::MoveLeft);
    rightAction    = new CameraAction(ActionType::CameraRight, Pi::SpectatorFlag::MoveRight);
    upAction       = new CameraAction(ActionType::CameraUp, Pi::SpectatorFlag::MoveUp);
    downAction     = new CameraAction(ActionType::CameraDown, Pi::SpectatorFlag::MoveDown);

    rotateTowerLeft = new TankAction(ActionType::TankTowerLeft, VehicleController::ControlCommand::TowerLeft);
    rotateTowerRight = new TankAction(ActionType::TankTowerRight, VehicleController::ControlCommand::TowerRight);

    tankForward = new TankAction(ActionType::TankForward, VehicleController::ControlCommand::Forward);
    tankBackward = new TankAction(ActionType::TankBackward, VehicleController::ControlCommand::Backward);
    tankLeft = new TankAction(ActionType::TankLeft, VehicleController::ControlCommand::Left);
    tankRigh = new TankAction(ActionType::TankRight, VehicleController::ControlCommand::Right);

    TheInputMgr->AddAction(forwardAction);
    TheInputMgr->AddAction(backwardAction);
    TheInputMgr->AddAction(leftAction);
    TheInputMgr->AddAction(rightAction);
    TheInputMgr->AddAction(upAction);
    TheInputMgr->AddAction(downAction);

    TheInputMgr->AddAction(tankForward);
    TheInputMgr->AddAction(tankBackward);
    TheInputMgr->AddAction(tankLeft);
    TheInputMgr->AddAction(tankRigh);

    TheInputMgr->AddAction(rotateTowerLeft);
    TheInputMgr->AddAction(rotateTowerRight);
}
