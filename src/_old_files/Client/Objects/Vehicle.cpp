#include "stdafx.h"
#include "Vehicle.h"



VehicleController::VehicleController() : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = false;
    movementFlags = 0;
    TheGame->SetVehicleController(this);

    modelAzimuth = 0.0F;
    modelAltitude = 0.0F;
}


VehicleController::VehicleController(float azimuth) : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = false;
    movementFlags = 0;
    TheGame->SetVehicleController(this);

    modelAzimuth = azimuth;
    modelAltitude = 0.0F;
}


VehicleController::VehicleController(float azimuth, bool player) : RigidBodyController(ControllerType::Vehicle)
{
    isPlayer = player;
    movementFlags = 0;
    TheGame->SetVehicleController(this);

    modelAzimuth = azimuth;
    modelAltitude = 0.0F;
}


VehicleController::~VehicleController()
{
}


bool VehicleController::ValidNode(const Node *node)
{
    /// Эта функция вызывается двигателем для определения этот конкретный тип контроллера может контролировать конкретный узел прошел через параметр узла.Эта функция должна верните true,
    /// если он может контролировать узел, а в противном случае он должен вернуть ложь. В этом случае контроллер может быть применен только моделировать узлы.

    return (node->GetNodeType() == Pi::NodeType::Model || node->GetNodeType() == Pi::NodeType::Geometry);
}


void VehicleController::Preprocess(void)
{
    /// Эта функция вызывается один раз, прежде чем целевой узел отрисован или перемещено. Функция базового класса Preprocess() должна всегда вызываться первым, а затем подкласс может делать
    /// все, что угодно предварительная обработка это нужно сделать.

    RigidBodyController::Preprocess();

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

        if (Pi::Text::CompareText(nodeName, "FrontLeft"))
        {
            wheelFrontLeft = thisNode;
        }
        else if (Pi::Text::CompareText(nodeName, "FrontRight"))
        {
            wheelFrontRight = thisNode;
        }
        else if (Pi::Text::CompareText(nodeName, "BackLeft"))
        {
            wheelBackLeft = thisNode;
        }
        else if (Pi::Text::CompareText(nodeName, "BackRight"))
        {
            wheelBackRight = thisNode;
        }
        else
        {
            /// здесь ничего
        }

        thisNode = root->GetNextNode(thisNode);
        nodeName = "NoName";
    } while (thisNode);

}


void VehicleController::Move(void)
{
    if (PiHEADLESS)
    {
        return;
    }

    float azm = modelAzimuth + TheInputMgr->GetMouseDeltaX();
    if (azm < - Pi::K::pi)
    {
        azm += Pi::K::two_pi;
    }
    else if (azm > Pi::K::pi)
    {
        azm -= Pi::K::two_pi;
    }
    else
    {
        /// здесь ничего
    }

    float alt = modelAltitude + TheInputMgr->GetMouseDeltaY();
    if (alt < -0.25F)
    {
        alt = -0.25F;
    }
    else if (alt > 1.45F)
    {
        alt = 1.45F;
    }
    else
    {
        /// здесь ничего
    }

    modelAzimuth = azm;
    modelAltitude = alt;

    //SetRigidBodyFlags(GetRigidBodyFlags() | RigidBodyFlag::KeepAwake);
    Vector3D vehicleForce = Vector3D(0.0F, 0.0F, 0.0F);

    float velocity = Magnitude(GetLinearVelocity());

    Node *target = GetTargetNode();
    Vector3D direction = target->GetNodeTransform()[0];
    SetExternalTorque(Vector3D(0.0F, 0.0F, 0.0F));

    if (!GroundContact())
    {
        direction.z = 0.0F;//no z component of force if not in ground contact
        speed = 30.0F;
    }
    else
    {
        speed = 60.0F;
    }

    SetExternalForce(vehicleForce);

    if (movementFlags & 1)
    {
        //Forward
        rotationalSpeed = 0.03F;
        SetExternalForce(0.8F * speed * direction);
    }
    else if (movementFlags & 2)
    {
        //Backward
        rotationalSpeed = -0.03F;
        SetExternalForce(-0.5F * speed * direction);
    }
    else
    {
        /// здесь ничего
    }

    if (movementFlags & 4)
    {
        //Right
        vehicleForce.y += 1.0F;
        SetExternalTorque(Vector3D(0.0F, 0.0F, speed / 20.0F));
        SetExternalAngularResistance(10.0F);
    }
    else if (movementFlags & 8)
    {
        //Left	
        SetExternalTorque(Vector3D(0.0F, 0.0F, -speed / 20.0F));
        SetExternalAngularResistance(10.0F);
    }
    else
    {
        /// здесь ничего
    }

    if (movementFlags & 16)
    {
        //Space
        SetExternalTorque(Vector3D(0.0F, 50.0F, 0.0F));
    }
    else if (!GroundContact())
    {
        SetExternalTorque(Vector3D(0.0F, 0.0F, 0.0F));
    }
    else
    {
        /// здесь ничего
    }

    SetRigidBodyFlags(GetRigidBodyFlags() | Pi::RigidBodyFlag::KeepAwake);

    SetExternalLinearResistance(Vector2D(2.0F, 2.0F));
    SetExternalAngularResistance(1.5F);

    if (velocity > 0.5F)
    {
        //only spin wheels if moving
        //RotateWheel(wheelFrontLeft);
        //RotateWheel(wheelFrontRight);
        //RotateWheel(wheelBackLeft);
        //RotateWheel(wheelBackRight);
    }
}


void VehicleController::RotateWheel(Node *wheelNode) {
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
    return Pi::RigidBodyStatus::Unchanged;
}


bool VehicleController::GroundContact(void) const
{
    const Contact *contact = GetFirstOutgoingEdge();
    while (contact)
    {
        Pi::ContactType::S type = contact->GetContactType();
        if (type == Pi::ContactType::Geometry)
        {
            const GeometryContact *geometryContact = static_cast<const GeometryContact *>(contact);
            if (geometryContact->GetRigidBodyContactNormal().z < -groundCosine)
            {
                return (true);
            }
        }
        else if (type == Pi::ContactType::RigidBody)
        {
            const RigidBodyContact *rigidBodyContact = static_cast<const RigidBodyContact *>(contact);
            if (rigidBodyContact->GetContactNormal().z < -groundCosine)
            {
                return true;
            }
        }
        else
        {
            /// здесь ничего
        }

        contact = contact->GetNextOutgoingEdge();
    }

    contact = GetFirstIncomingEdge();
    while (contact)
    {
        if (contact->GetContactType() == Pi::ContactType::RigidBody)
        {
            const RigidBodyContact *rigidBodyContact = static_cast<const RigidBodyContact *>(contact);
            if (rigidBodyContact->GetContactNormal().z > groundCosine)
            {
                return (true);
            }
        }

        contact = contact->GetNextIncomingEdge();
    }

    return (false);
}
