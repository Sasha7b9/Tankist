#pragma once
#include "GameObjects.h"


enum : Pi::ControllerType
{
    kControllerTank = 'tank'
};


enum : Pi::ModelType
{
    kModelTank = 'tank'
};


class TankController;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank
{
public:

    static void Construct();
    static void Destruct();

    static Tank *Create();

    Model *GetModel() { return model; }

    TankController *GetController() { return (TankController *)model->GetController(); };

private:

    ControllerReg<TankController>   tankControllerRegistration;
    ModelRegistration               tankModelRegistration;

    Tank(Model *model = nullptr);
    ~Tank();

    Model *model = nullptr;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankInteractor : public Pi::Interactor
{
private:
    TankController *tankController = nullptr;
public:
    TankInteractor(TankController *controller);
    ~TankInteractor();

    virtual void HandleInteractionEvent(Pi::InteractionEventType type, Node *node, const Point3D *position) override;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankController final : public GameObjectController
{
public:

    enum
    {
        kNone,
        kTowerLeft  = 1 << 0,  ///< Поворот башни влево
        kTowerRight = 1 << 1,  ///< Поворот башни вправо
        kForward    = 1 << 2,
        kBackward   = 1 << 3,
        kLeft       = 1 << 4,
        kRight      = 1 << 5
    };


    TankController();
    ~TankController();

    TankInteractor tankInteractor;

    void Preprocess() override;

    void Move() override;

    static bool ValidNode(const Node *node);

    void AddMovementFlag(uint flag) { flagsMovement |= flag; };

    void RemoveMovementFlag(uint flag) { flagsMovement &= ~flag; };

private:

    Node *nodeTower = nullptr;
    Node *nodeBarrel1 = nullptr;
    Node *nodeBarrel2 = nullptr;
    Node *nodeBody = nullptr;
    Node *nodeTrackLeft = nullptr;
    Node *nodeTrackRight = nullptr;
    Node *nodeRoot = nullptr;

    float azimuthTower = 0.0F;

    Point3D azimuthBody = { 0.0F, 0.0F, 0.0F };

    uint flagsMovement = 0;

    float speed = 0.001F;

    TankController(const TankController &tankController);

    void Construct();

    Controller *Replicate() const override;

    Node *GetSubnode(const char* name);

    void SetPositionCamera();
};
