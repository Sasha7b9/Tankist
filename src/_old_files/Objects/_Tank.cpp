#include <stdafx.h>
#include "Tank.h"
#include "globals.h"


namespace
{
    Storage<Tank> tankStorage;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tank::Tank(Model *_model) :
    tankControllerRegistration(kControllerTank, "Tank"),
    tankModelRegistration(kModelTank, "Tank", "models/Tank", Pi::kModelPrecache, kControllerTank),
    model(_model)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Tank::~Tank()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Tank::Construct()
{
    new(tankStorage)Tank();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Tank::Destruct()
{
    tankStorage->~Tank();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Tank* Tank::Create()
{
    Model *model = Model::Get(kModelTank);

    TankController *controller = new TankController();
    model->SetController(controller);

    DefaultParameters params(0.05f, {0.0f, 0.0f, 90.0f * Pi::K::radians});

    (static_cast<GameObjectController*>(model->GetController()))->SetDefaultParameters(&params);

    //Node *node = model->GetFirstSubnode();
    //
    //while (node)
    //{
    //    TheConsoleWindow->AddText(node->GetNodeName());
    //    node = node->Next();
    //}

    return new Tank(model);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TankInteractor::TankInteractor(TankController *controller) :
    tankController(controller)
{
    
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TankInteractor::~TankInteractor()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TankInteractor::HandleInteractionEvent(Pi::InteractionEventType type, Node *node, const Point3D *position)
{
    Interactor::HandleInteractionEvent(type, node, position);
    Controller *controller = node->GetController();
    if (controller)
    {
        controller->HandleInteractionEvent(type, position);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TankController::TankController() :
    GameObjectController(kGameObjectUnit, kControllerTank),
    tankInteractor(this)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TankController::TankController(const TankController& tankController) :
    GameObjectController(tankController),
    tankInteractor(this)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TankController::~TankController()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Controller *TankController::Replicate() const
{
    return new TankController(*this);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TankController::Preprocess()
{
    GameObjectController::Preprocess();

    Construct();

    SetRigidBodyFlags(Pi::kRigidBodyKeepAwake | Pi::kRigidBodyFixedOrientation);
    SetFrictionCoefficient(0.0F);
    SetLinearVelocity(Pi::Math::RandomUnitVector3D() * 2.0F);

    const Node *target = GetTargetNode();

    const Node *node = target;

    do
    {
        if (node->GetNodeType() == Pi::kNodeGeometry)
        {
            GeometryObject *object = static_cast<const Geometry *>(node)->GetObject();
            object->SetGeometryFlags(object->GetGeometryFlags() | Pi::kGeometryDynamic);
        }

        node = target->GetNextNode(node);
    } while (node);

    Transform4D transform = nodeRoot->GetNodeTransform();
    transform.SetRotationAboutZ(azimuthBody.x);
    transform.SetTranslation(nodeRoot->GetNodePosition());
    nodeRoot->SetNodeTransform(transform);

    transform = nodeBody->GetNodeTransform();
    transform.SetRotationAboutZ(3.14F / 2.0F);
    nodeBody->SetNodeTransform(transform);

    TheWorldMgr->GetWorld()->AddInteractor(&tankInteractor);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Node *TankController::GetSubnode(const char* name)
{
    Node *node = GetTargetNode()->GetFirstSubnode();
    
    while (node)
    {
        const char* nodeName = node->GetNodeName();
    
        if (nodeName)
        {
            if (strcmp(nodeName, name) == 0)
            {
                return node;
            }
        }
    
        node = node->Next();
    }
    
    return node;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TankController::Construct()
{
    nodeTower = GetSubnode("Cylinder001");
    nodeBarrel1 = GetSubnode("Cylinder002");
    nodeBarrel2 = GetSubnode("Cylinder003");
    nodeBody = GetSubnode("Box001");
    nodeTrackLeft = GetSubnode("Box002");
    nodeTrackRight = GetSubnode("Box003");

    if (nodeTower)
    {
        nodeTower->AppendSubnode(nodeBarrel1);
        nodeBarrel1->AppendSubnode(nodeBarrel2);
        nodeBody->AppendSubnode(nodeTower);
        nodeBody->AppendSubnode(nodeTrackLeft);
        nodeBody->AppendSubnode(nodeTrackRight);

        nodeRoot = GetTargetNode();

        TheGizmo = new Gizmo(nodeRoot);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TankController::Move()
{
    GameObjectController::Move();

    if (flagsMovement == 0)
    {
        return;
    }

    /*
    if (flagsMovement & kTowerLeft || flagsMovement & kTowerRight)
    {
        if (!((flagsMovement & kTowerLeft) && (flagsMovement & kTowerRight)))
        {
            float sign = (flagsMovement & kTowerLeft) ? 1.0F : -1.0F;

            azimuthTower += 1e-3F * sign * TheTimeMgr->GetDeltaTime();

            Transform4D transform = nodeTower->GetNodeTransform();

            transform.SetRotationAboutZ(azimuthTower);

            nodeTower->SetNodeTransform(transform);

            nodeTower->Invalidate();
        }
    }

    if (flagsMovement & kLeft || flagsMovement & kRight)
    {
        if (!((flagsMovement & kLeft) && (flagsMovement & kRight)))
        {
            float sign = (flagsMovement & kLeft) ? 1.0F : -1.0F;

            azimuthBody.x += 1e-3F * sign * TheTimeMgr->GetDeltaTime();

            Transform4D transform = nodeRoot->GetNodeTransform();

            transform.SetRotationAboutZ(azimuthBody.x);

            transform.SetTranslation(nodeRoot->GetNodePosition());

            nodeRoot->SetNodeTransform(transform);

            nodeRoot->Invalidate();
        }
    }

    if (flagsMovement & kForward || flagsMovement & kBackward)
    {
        if (!((flagsMovement & kForward) && (flagsMovement & kBackward)))
        {
            Point3D translation =  nodeRoot->GetNodeTransform().GetTranslation();

            float sign = (flagsMovement & kForward) ? 1.0F : -1.0F;

            float distance = sign * speed * TheTimeMgr->GetDeltaTime();

            translation.x += distance * cosf(azimuthBody.x);
            translation.y += distance * sinf(azimuthBody.x);

            nodeRoot->SetNodePosition(translation);

            nodeRoot->Invalidate();
        }
    }

    */

    if (flagsMovement)
    {
        flagsMovement = 0;
        ApplyImpulse({ 10.0F, 10.0F, 0.0F });
    }

    SetPositionCamera();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TankController::SetPositionCamera()
{
    nodeRoot->AppendSubnode(TheWorldMgr->GetWorld()->GetCamera());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool TankController::ValidNode(const Node *node)
{
    return node->GetNodeType() == Pi::kNodeModel;
}
