#pragma once


namespace ControllerType
{
    const Pi::ControllerType::S Vehicle = 'ctrv';
}

namespace ModelType
{
    const Pi::ControllerType::S Vehicle = 'vcle';
};



class VehicleController : public RigidBodyController
{

private:
    uint    movementFlags;
    float	groundCosine;

    float   modelAzimuth;
    float   modelAltitude;
    float   tankAzimuth;

    /// Эти узлы представляют геометрию колеса
    Node *wheelFrontLeft;
    Node *wheelFrontRight;
    Node *wheelBackLeft;
    Node *wheelBackRight;

    float speed;            ///< Коэффициент умножения внешних сил на автомобиль
    float rotationalSpeed;  ///< Используется для определения скорости вращения колеса

public:

    RigidBodyStatus::E HandleNewGeometryContact(const Pi::GeometryContact *contact);

    bool	isPlayer;

    VehicleController(float azimuth);
    VehicleController(float azimuth, bool isPlayer);

    VehicleController();
    ~VehicleController();

    static bool ValidNode(const Node *node);

    void Preprocess(void);
    void Move(void);

    void RotateWheel(Node *wheel);

    unsigned long GetMovementFlags(void) const
    {
        return (movementFlags);
    }

    void SetMovementFlags(unsigned long flags)
    {
        movementFlags = flags;
    }

    float GetGroundCosine(void) const
    {
        return (groundCosine);
    }

    void SetGroundCosine(float cosine)
    {
        groundCosine = cosine;
    }

    bool GroundContact(void) const;


    float GetModelAzimuth(void) const
    {
        return (modelAzimuth);
    }

    float GetModelAltitude(void) const
    {
        return (modelAltitude);
    }

    struct ControlCommand
    {
        typedef uint B;

        static const B Forward    = 1 << 0;
        static const B Backward   = 1 << 1;
        static const B Left       = 1 << 2;
        static const B Right      = 1 << 3;
        static const B TowerLeft  = 1 << 4;
        static const B TowerRight = 1 << 5;
    };
};
