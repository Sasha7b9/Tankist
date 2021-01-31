#include "stdafx.h"

using namespace Pi;


VehicleController::VehicleController() : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = false;
    movementFlags = 0;
//    TheGame->SetVehicleController(this);

    modelAzimuth = 0.0F;
    modelAltitude = 0.0F;
}


VehicleController::VehicleController(float azimuth) : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = false;
    movementFlags = 0;
//    TheGame->SetVehicleController(this);

    modelAzimuth = azimuth;
    modelAltitude = 0.0F;
}


VehicleController::VehicleController(float azimuth, bool player) : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = player;
    movementFlags = 0;
//    TheGame->SetVehicleController(this);

    modelAzimuth = azimuth;
    modelAltitude = 0.0F;
}


VehicleController::~VehicleController()
{
}


bool VehicleController::ValidNode(const Node *node)
{
    // Эта функция вызывается двигателем для определения этот конкретный тип контроллера может контролировать конкретный узел прошел через параметр узла.Эта функция должна верните true,
    // если он может контролировать узел, а в противном случае он должен вернуть ложь. В этом случае контроллер может быть применен только моделировать узлы.

    return (node->GetNodeType() == NodeType::Model || node->GetNodeType() == NodeType::Geometry);
}


void VehicleController::Preprocess(void)
{
    // Эта функция вызывается один раз, прежде чем целевой узел отрисован или перемещено. Функция базового класса Preprocess() должна всегда вызываться первым, а затем подкласс может делать
    // все, что угодно предварительная обработка это нужно сделать.

    RigidBodyController::Preprocess();

    //SetRigidBodyFlags(GetRigidBodyFlags() | RigidBodyFlag::LocalSimulation);

    SetRestitutionCoefficient(0.0F);
    SetGravityMultiplier(3.0F);

    groundCosine = 0.25F;
    speed = 0.0F;
    rotationalSpeed = 0.0F;

    Node *root = GetTargetNode();
    Node *thisNode = root;

    String<30> nodeName = "NoName";

    if (thisNode->GetNodeName())
    {
        nodeName = thisNode->GetNodeName();
    }

    do
    {
        if (thisNode->GetNodeName())
        {
            nodeName = thisNode->GetNodeName();
        }

        if (Text::CompareText(nodeName, "FrontLeft"))
        {
            wheelFrontLeft = thisNode;
        }
        else if (Text::CompareText(nodeName, "FrontRight"))
        {
            wheelFrontRight = thisNode;
        }
        else if (Text::CompareText(nodeName, "BackLeft"))
        {
            wheelBackLeft = thisNode;
        }
        else if (Text::CompareText(nodeName, "BackRight"))
        {
            wheelBackRight = thisNode;
        }
        else
        {
            // здесь ничего
        }

        thisNode = root->GetNextNode(thisNode);
        nodeName = "NoName";
    } while (thisNode);

}

void VehicleController::Move(void)
{
    if (!PiHEADLESS)
    {
        float azm = modelAzimuth + TheInputMgr->GetMouseDeltaX();
        if (azm < -K::pi)
        {
            azm += K::two_pi;
        }
        else if (azm > K::pi) //-V2516
        {
            azm -= K::two_pi;
        }

        float alt = modelAltitude + TheInputMgr->GetMouseDeltaY();
        if (alt < -1.45F)
        {
            alt = -1.45F;
        }
        else if (alt > 1.45F) //-V2516
        {
            alt = 1.45F;
        }

        modelAzimuth = azm;
        modelAltitude = alt;
    }

    // Узнаём абсолютную величину скорости
    float velocity = Magnitude(GetLinearVelocity());

    Node *target = GetTargetNode();

    // Направление движения модели
    Vector3D direction = target->GetNodeTransform()[0];
//    SetExternalTorque(Vector3D(0.0F, 0.0F, 0.0F));

    if(!GroundContact())
    {
        direction.z = 0.0F;//no z component of force if not in ground contact
        speed = 30.0F;
    }
    else
    {
        speed = 60.0F;
    }

    SetExternalForce({ 0.0F, 0.0F, 0.0F });

    if (movementFlags & kMovementUp)
    {
        if (!alreadyUp)
        {
            if (GroundContact())
            {
                ApplyImpulse({ 0.0F, 0.0F, speed / 5.0F });
                alreadyUp = true;
            }
        }
    }
    else
    {
        alreadyUp = false;
    }

    if(movementFlags & kMovementForward)
    {
        rotationalSpeed = 0.03F;
        SetExternalForce(0.8F * speed * direction);
    }
    else if(movementFlags & kMovementBackward) //-V2516
    {
        rotationalSpeed = -0.03F;
        SetExternalForce(-0.5F * speed * direction);
    }

    if(movementFlags & kMovementRight)
    {
        float s = (movementFlags & kMovementForward) ? (-speed / 20.0F) : (speed / 20.0F);

        SetExternalTorque(Vector3D(0.0F, 0.0F, s));
        SetExternalAngularResistance(10.0F);
    }
    else if (movementFlags & kMovementLeft)
    {
        float s = (movementFlags & kMovementForward) ? (speed / 20.0F) : (-speed / 20.0F);

        SetExternalTorque(Vector3D(0.0F, 0.0F, s));
        SetExternalAngularResistance(10.0F);
    }
    else
    {
        Vector3D torgue = GetExternalTorque();
        torgue.z = - torgue.z;
        SetExternalTorque(torgue);
    }

    if(movementFlags & 16)
    {
        //Space
        SetExternalTorque(Vector3D(0.0F, 50.0F, 0.0F));
    }
    else if(!GroundContact()) //-V2516
    {
        SetExternalTorque(Vector3D(0.0F, 0.0F, 0.0F));
    }

    SetRigidBodyFlags(GetRigidBodyFlags() | RigidBodyFlag::KeepAwake);

    SetExternalLinearResistance(Vector2D(2.0F, 2.0F));
    SetExternalAngularResistance(1.5F);

    if(velocity > 0.5F)
    {
        //only spin wheels if moving
        //RotateWheel(wheelFrontLeft);
        //RotateWheel(wheelFrontRight);
        //RotateWheel(wheelBackLeft);
        //RotateWheel(wheelBackRight);
    }
}


void VehicleController::RotateWheel(Node *wheelNode)
{
    float velocity = Magnitude(GetLinearVelocity());
    Transform4D WheelTransform = wheelNode->GetNodeTransform();
    Vector3D down = WheelTransform[2];
    Vector3D axis = WheelTransform[1];
    Vector3D front = WheelTransform[0];
    float deltaAngle = velocity * rotationalSpeed;
    front = front.RotateAboutAxis(deltaAngle, axis);
    down = down.RotateAboutAxis(deltaAngle, axis);
    wheelNode->SetNodeMatrix3D(front, axis, down);
    wheelNode->Invalidate();
}


RigidBodyStatus::E VehicleController::HandleNewGeometryContact(const GeometryContact *)
{
    return (RigidBodyStatus::Unchanged);
}


bool VehicleController::GroundContact(void) const //-V2506
{
    const Contact *contact = GetFirstOutgoingEdge();
    while(contact)
    {
        ContactType::S type = contact->GetContactType();
        if(type == ContactType::Geometry)
        {
            const GeometryContact *geometryContact = static_cast<const GeometryContact *>(contact);
            if(geometryContact->GetRigidBodyContactNormal().z < -groundCosine)
            {
                return (true);
            }
        }
        else if(type == ContactType::RigidBody)
        {
            const RigidBodyContact *rigidBodyContact = static_cast<const RigidBodyContact *>(contact);
            if(rigidBodyContact->GetContactNormal().z < -groundCosine)
            {
                return true;
            }
        }
        else
        {
            // здесь ничего
        }

        contact = contact->GetNextOutgoingEdge();
    }

    contact = GetFirstIncomingEdge();
    while(contact)
    {
        if(contact->GetContactType() == ContactType::RigidBody)
        {
            const RigidBodyContact *rigidBodyContact = static_cast<const RigidBodyContact *>(contact);
            if(rigidBodyContact->GetContactNormal().z > groundCosine)
            {
                return (true);
            }
        }

        contact = contact->GetNextIncomingEdge();
    }

    return (false);
}


UseAction::UseAction() : Action(ActionType::Fire)
{
}


UseAction::~UseAction()
{
}


void UseAction::Begin(void)
{
    // Игрок нажал кнопку огня / использования. Если мы в настоящее время взаимодействуем с узел в сцене, и этот узел имеет контроллер, затем мы отправляем событие активации на этот
    // контроллер, чтобы он знал, что игрок что - то делает с ним.
}


void UseAction::End(void)
{
    // Игрок отпустил кнопку огня / использования. Пусть узел, с которым мы взаимодействуем Знайте, что мы закончили с этим, отправив его контролеру событие деактивации.
}
