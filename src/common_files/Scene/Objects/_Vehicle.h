/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


namespace Urho3D
{
    class Constraint;
    class Node;
    class RigidBody;
}

using namespace Urho3D;

const unsigned CTRL_FORWARD = (1u << 0u);
const unsigned CTRL_BACK = (1u << 1u);
const unsigned CTRL_LEFT = (1u << 2u);
const unsigned CTRL_RIGHT = (1u << 3u);
const unsigned CTRL_BRAKE = (1u << 4u);
const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;


struct VehicleLogicState : public ObjectState
{
    float steering_ = 0.0f;                 // Current left/right steering amount (-1 to 1.)
    float vehicleSteering_ = 0.0f;          // Tmp storage for steering
    float engineForce_ = 0.0f;              // Linear momentum supplied by engine to RigidBody
    float brakingForce_ = 50.0f;            // Rotational momentum preventing (dampening) wheels rotation
    float maxEngineForce_ = 2500.0f;        // Maximum linear momentum supplied by engine to RigidBody
    float wheelRadius_ = 0.5f;              // Stored wheel radius
    float suspensionRestLength_ = 0.6f;     // Suspension rest length (in meters)
    float wheelWidth_ = 0.4f;               // Width of wheel (used only in calculation of wheel placement)
    float suspensionStiffness_ = 14.0f;     // Suspension stiffness
    float suspensionDamping_ = 2.0f;        // Suspension damping
    float suspensionCompression_ = 4.0f;    // Suspension compression
    float wheelFriction_ = 1000.0f;         // Wheel friction
    float rollInfluence_ = 0.12f;           // Wheel roll influence (how much car will turn sidewise)
    bool emittersCreated = false;           // Do not recreate emitters if they are already created.

    virtual void Compress(VectorBuffer &buffer) const override;
    virtual void Decompress(MemoryBuffer &buffer) override;

    Node *node = nullptr;
};


// Vehicle component, responsible for physical movement according to controls.
// Encapsulates RaycastVehicle
class VehicleLogic : public LogicComponent
{
    URHO3D_OBJECT(VehicleLogic, LogicComponent)

public :
    /// Construct.
    explicit VehicleLogic(Context* context);
    /// Destruct.
    ~VehicleLogic() override;

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Perform post-load after deserialization. Acquire the components from the scene nodes.
    void ApplyAttributes() override;

    /// Initialize the vehicle. Create rendering and physics components. Called by the application.
    void Init();

    /// Handle physics world update. Called by LogicComponent base class.
    void FixedUpdate(float timeStep) override;
    /// Updating wheel effects here.
    void PostUpdate(float timeStep) override;

    /// Movement controls.
    Controls controls_;

    /// Get steering value.
    float GetSteering() { return steering_; }

    /// Set steering value.
    void SetSteering(float steering) { steering_ = steering; }

    /// Get wheel radius.
    float GetWheelRadius() { return wheelRadius_; }

    /// Get wheel width.
    float GetWheelWidth() { return wheelWidth_; }

    void UpdateControls(Key key, bool press);

    bool IsControlVehicle(Key key);

    VehicleLogicState *GetState() { return &state; };

private:
    /// Creates particle emitter.
    void CreateEmitter(const Vector3 &place);

    VehicleLogicState state;

    float &steering_ = state.steering_;
    float &vehicleSteering_ = state.vehicleSteering_;
    float &engineForce_ = state.engineForce_;
    float &brakingForce_ = state.brakingForce_;
    float &maxEngineForce_ = state.maxEngineForce_;
    float &wheelRadius_ = state.wheelRadius_;
    float &suspensionRestLength_ = state.suspensionRestLength_;
    float &wheelWidth_ = state.wheelWidth_;
    float &suspensionStiffness_ = state.suspensionStiffness_;
    float &suspensionDamping_ = state.suspensionDamping_;
    float &suspensionCompression_ = state.suspensionCompression_;
    float &wheelFriction_ = state.wheelFriction_;
    float &rollInfluence_ = state.rollInfluence_;

    bool &emittersCreated = state.emittersCreated;
    
    Vector<Node*> particleEmitterNodeList_;     // Emitter data for saving.
    Vector3 prevVelocity_;                      // Value to calculate acceleration.
    Vector3 connectionPoints_[4];               // Storing points for emitters
    
};


class Vehicle : public Object
{
    URHO3D_OBJECT(Vehicle, Object);

public:

    Vehicle(Context *context);

    virtual ~Vehicle() {};

    WeakPtr<VehicleLogic> logic;
};
