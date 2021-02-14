/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


const float CHASSIS_WIDTH = 2.6f;


void VehicleLogic::RegisterObject(Context* context)
{
    context->RegisterFactory<VehicleLogic>();
    URHO3D_ATTRIBUTE("Steering", float, steering_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Controls Yaw", float, controls_.yaw_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Controls Pitch", float, controls_.pitch_, 0.0f, AM_DEFAULT);
}

VehicleLogic::VehicleLogic(Context* context)
    : LogicComponent(context)
{
    SetUpdateEventMask(USE_FIXEDUPDATE | USE_POSTUPDATE);
}

VehicleLogic::~VehicleLogic() = default;

void VehicleLogic::Init()
{
    state.node = GetNode();

    auto* vehicle = node_->CreateComponent<RaycastVehicle>();
    vehicle->Init();
    auto* hullBody = node_->GetComponent<RigidBody>();
    hullBody->SetMass(800.0f);
    hullBody->SetLinearDamping(0.2f); // Some air resistance
    hullBody->SetAngularDamping(0.5f);
    hullBody->SetCollisionLayer(1);
    // This function is called only from the main program when initially creating the vehicle, not on scene load
    auto* cache = GetSubsystem<ResourceCache>();
    auto* hullObject = node_->CreateComponent<StaticModel>();
    // Setting-up collision shape
    auto* hullColShape = node_->CreateComponent<CollisionShape>();
    Vector3 v3BoxExtents = Vector3::ONE;
    hullColShape->SetBox(v3BoxExtents);
    node_->SetScale(Vector3(2.3f, 1.0f, 4.0f));
    hullObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    hullObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    hullObject->SetCastShadows(true);
    float connectionHeight = -0.4f;
//    bool isFrontWheel = true;
    Vector3 wheelDirection(0, -1, 0);
    Vector3 wheelAxle(-1, 0, 0);
    // We use not scaled coordinates here as everything will be scaled.
    // Wheels are on bottom at edges of the chassis
    // Note we don't set wheel nodes as children of hull (while we could) to avoid scaling to affect them.
    float wheelX = CHASSIS_WIDTH / 2.0f - wheelWidth_;
    // Front left
    connectionPoints_[0] = Vector3(-wheelX, connectionHeight, 2.5f - GetWheelRadius() * 2.0f);
    // Front right
    connectionPoints_[1] = Vector3(wheelX, connectionHeight, 2.5f - GetWheelRadius() * 2.0f);
    // Back left
    connectionPoints_[2] = Vector3(-wheelX, connectionHeight, -2.5f + GetWheelRadius() * 2.0f);
    // Back right
    connectionPoints_[3] = Vector3(wheelX, connectionHeight, -2.5f + GetWheelRadius() * 2.0f);
    const Color LtBrown(0.972f, 0.780f, 0.412f);
    for (int id = 0; id < (int)sizeof(connectionPoints_) / (int)sizeof(connectionPoints_[0]); id++)
    {
        Node* wheelNode = GetScene()->CreateChild();
        Vector3 connectionPoint = connectionPoints_[id];
        // Front wheels are at front (z > 0)
        // back wheels are at z < 0
        // Setting rotation according to wheel position
        bool isFrontWheel = connectionPoints_[id].z_ > 0.0f;
        wheelNode->SetRotation(connectionPoint.x_ >= 0.0 ? Quaternion(0.0f, 0.0f, -90.0f) : Quaternion(0.0f, 0.0f, 90.0f));
        wheelNode->SetWorldPosition(node_->GetWorldPosition() + node_->GetWorldRotation() * connectionPoints_[id]);
        vehicle->AddWheel(wheelNode, wheelDirection, wheelAxle, suspensionRestLength_, wheelRadius_, isFrontWheel);
        vehicle->SetWheelSuspensionStiffness(id, suspensionStiffness_);
        vehicle->SetWheelDampingRelaxation(id, suspensionDamping_);
        vehicle->SetWheelDampingCompression(id, suspensionCompression_);
        vehicle->SetWheelFrictionSlip(id, wheelFriction_);
        vehicle->SetWheelRollInfluence(id, rollInfluence_);
        wheelNode->SetScale(Vector3(1.0f, 0.65f, 1.0f));
        auto* pWheel = wheelNode->CreateComponent<StaticModel>();
        pWheel->SetModel(cache->GetResource<Model>("Models/Cylinder.mdl"));
        pWheel->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        pWheel->SetCastShadows(true);
        CreateEmitter(connectionPoints_[id]);
    }
    emittersCreated = true;
    vehicle->ResetWheels();
}

void VehicleLogic::CreateEmitter(const Vector3 &place)
{
    auto* cache = GetSubsystem<ResourceCache>();
    Node* emitter = GetScene()->CreateChild();
    emitter->SetWorldPosition(node_->GetWorldPosition() + node_->GetWorldRotation() * place + Vector3(0, -wheelRadius_, 0));
    auto* particleEmitter = emitter->CreateComponent<ParticleEmitter>();
    particleEmitter->SetEffect(cache->GetResource<ParticleEffect>("Particle/Dust.xml"));
    particleEmitter->SetEmitting(false);
    particleEmitterNodeList_.Push(emitter);
    emitter->SetTemporary(true);
}

/// Applying attributes
void VehicleLogic::ApplyAttributes()
{
//    auto* vehicle = node_->GetOrCreateComponent<RaycastVehicle>();
    if (emittersCreated)
        return;
    for (const auto& connectionPoint : connectionPoints_)
    {
        CreateEmitter(connectionPoint);
    }
    emittersCreated = true;
}

void VehicleLogic::FixedUpdate(float)
{
    float newSteering = 0.0f;
    float accelerator = 0.0f;
    bool brake = false;
    auto* vehicle = node_->GetComponent<RaycastVehicle>();
    // Read controls
    if (controls_.buttons_ & CTRL_LEFT)
    {
        newSteering = -1.0f;
    }
    if (controls_.buttons_ & CTRL_RIGHT)
    {
        newSteering = 1.0f;
    }
    if (controls_.buttons_ & CTRL_FORWARD)
    {
        accelerator = 1.0f;
    }
    if (controls_.buttons_ & CTRL_BACK)
    {
        accelerator = -0.5f;
    }
    if (controls_.buttons_ & CTRL_BRAKE)
    {
        brake = true;
    }
    // When steering, wake up the wheel rigidbodies so that their orientation is updated
    if (newSteering != 0.0f) //-V550
    {
        SetSteering(GetSteering() * 0.95f + newSteering * 0.05f);
    }
    else
    {
        SetSteering(GetSteering() * 0.8f + newSteering * 0.2f);
    }
    // Set front wheel angles
    vehicleSteering_ = steering_;
    int wheelIndex = 0;
    vehicle->SetSteeringValue(wheelIndex, vehicleSteering_);
    wheelIndex = 1;
    vehicle->SetSteeringValue(wheelIndex, vehicleSteering_);
    // apply forces
    engineForce_ = maxEngineForce_ * accelerator;
    // 2x wheel drive
    vehicle->SetEngineForce(2, engineForce_);
    vehicle->SetEngineForce(3, engineForce_);
    for (int i = 0; i < vehicle->GetNumWheels(); i++)
    {
        if (brake)
        {
            vehicle->SetBrake(i, brakingForce_);
        }
        else
        {
            vehicle->SetBrake(i, 0.0f);
        }
    }
}

void VehicleLogic::PostUpdate(float timeStep)
{
    auto* vehicle = node_->GetComponent<RaycastVehicle>();
    auto* vehicleBody = node_->GetComponent<RigidBody>();
    Vector3 velocity = vehicleBody->GetLinearVelocity();
    Vector3 accel = (velocity - prevVelocity_) / timeStep;
    float planeAccel = Vector3(accel.x_, 0.0f, accel.z_).Length();
    for (int i = 0; i < vehicle->GetNumWheels(); i++)
    {
        Node* emitter = particleEmitterNodeList_[(uint)i];
        auto* particleEmitter = emitter->GetComponent<ParticleEmitter>();
        if (vehicle->WheelIsGrounded(i) && (vehicle->GetWheelSkidInfoCumulative(i) < 0.9f || vehicle->GetBrake(i) > 2.0f ||
            planeAccel > 15.0f))
        {
            particleEmitterNodeList_[(size_t)i]->SetWorldPosition(vehicle->GetContactPosition(i));
            if (!particleEmitter->IsEmitting())
            {
                particleEmitter->SetEmitting(true);
            }
//            URHO3D_LOGDEBUG("GetWheelSkidInfoCumulative() = " +
//                            String(vehicle->GetWheelSkidInfoCumulative(i)) + " " +
//                            String(vehicle->GetMaxSideSlipSpeed()));
            /* TODO: Add skid marks here */
        }
        else if (particleEmitter->IsEmitting())
        {
            particleEmitter->SetEmitting(false);
        }
    }
    prevVelocity_ = velocity;
}


Vehicle::Vehicle(Context *context) : Object(context)
{
    Node *node = TheScene->CreateChild("Vehicle");

    node->SetPosition(Vector3(0.0f, 25.0f, 0.0f));

    // Create the vehicle logic component
    logic = node->CreateComponent<VehicleLogic>();

    // Create the rendering and physics components
    logic->Init();
}


void VehicleLogic::UpdateControls(Key key, bool press)
{
    if (IsControlVehicle(key))
    {
#ifdef CLIENT

        Message::KeyEvent(key, press).Send(true);

#elif defined SERVER

        URHO3D_LOGINFOF("Key %d", key);
        if      (key == KEY_W) { controls_.Set(CTRL_FORWARD, press); }
        else if (key == KEY_S) { controls_.Set(CTRL_BACK, press); }
        else if (key == KEY_A) { controls_.Set(CTRL_LEFT, press); }
        else if (key == KEY_D) { controls_.Set(CTRL_RIGHT, press); }
        else if (key == KEY_F) { controls_.Set(CTRL_BRAKE, press); }

#endif
    }
}


bool VehicleLogic::IsControlVehicle(Key key)
{
    return (key == KEY_W) ||
        (key == KEY_S) ||
        (key == KEY_A) ||
        (key == KEY_D) ||
        (key == KEY_F);
}


void VehicleLogicState::Compress(VectorBuffer &buffer) const
{
    buffer.WriteVector3(node->GetPosition());
    buffer.WriteQuaternion(node->GetRotation());

    buffer.WriteFloat(steering_);
    buffer.WriteFloat(vehicleSteering_);
    buffer.WriteFloat(engineForce_);
    buffer.WriteFloat(brakingForce_);
    buffer.WriteFloat(maxEngineForce_);
    buffer.WriteFloat(wheelRadius_);
    buffer.WriteFloat(suspensionRestLength_);
    buffer.WriteFloat(wheelWidth_);
    buffer.WriteFloat(suspensionStiffness_);
    buffer.WriteFloat(suspensionDamping_);
    buffer.WriteFloat(suspensionCompression_);
    buffer.WriteFloat(wheelFriction_);
    buffer.WriteFloat(rollInfluence_);

    buffer.WriteBool(emittersCreated);
}


void VehicleLogicState::Decompress(MemoryBuffer &buffer)
{
    node->SetPosition(buffer.ReadVector3());
    node->SetRotation(buffer.ReadQuaternion());

    steering_ = buffer.ReadFloat();
    vehicleSteering_ = buffer.ReadFloat();
    engineForce_ = buffer.ReadFloat();
    brakingForce_ = buffer.ReadFloat();
    maxEngineForce_ = buffer.ReadFloat();
    wheelRadius_ = buffer.ReadFloat();
    suspensionRestLength_ = buffer.ReadFloat();
    wheelWidth_ = buffer.ReadFloat();
    suspensionStiffness_ = buffer.ReadFloat();
    suspensionDamping_ = buffer.ReadFloat();
    suspensionCompression_ = buffer.ReadFloat();
    wheelFriction_ = buffer.ReadFloat();
    rollInfluence_ = buffer.ReadFloat();

    emittersCreated = buffer.ReadBool();

#ifdef CLIENT
    TheMainCamera->ConnectTo(node);
#endif
}
