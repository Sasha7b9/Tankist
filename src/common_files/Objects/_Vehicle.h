#pragma once


namespace Pi
{
    // Типы моделей связаны с ресурсом модели с помощью ModelRegistration учебный класс.Модели регистрируются с помощью движка в конструкторе Game.
    namespace ModelType
    {
        static const S Vehicle = 'vcle';
    };
    
    // Новые типы контроллеров регистрируются с помощью движка в конструкторе Game. Это типы контроллеров, которые мы используем для перемещения автомобиля и запускаемых им ракет.
    namespace ControllerType
    {
        static const S Vehicle = 'ctrv';
    };
    
    // Новые типы локаторов регистрируются с помощью движка в конструкторе Game. Локатор 'spawn' используется, чтобы указать, где игрок должен быть расположен, когда мир загружен.
    enum
    {
        kLocatorSpawn = 'spwn'
    };

  
    class UseAction : public Action
    {
    public:

        UseAction();
        ~UseAction();

        void Begin(void);
        void End(void);
    };


    
    class VehicleController : public RigidBodyController
    {

    private:
        unsigned long		movementFlags; //-V126
        float				groundCosine = 0.0F;

        float				modelAzimuth;
        float				modelAltitude;
        float				tankAzimuth = 0.0F;

        // Эти узлы представляют геометрию колеса
        Node *wheelFrontLeft = nullptr; //-V122
        Node *wheelFrontRight = nullptr; //-V122
        Node *wheelBackLeft = nullptr; //-V122
        Node *wheelBackRight = nullptr; //-V122

        float speed = 0.0F;                 // Коэффициент умножения внешних сил на автомобиль
        float rotationalSpeed = 0.0F;       // Используется для определения скорости вращения колеса

        bool alreadyUp = false;             // Признак того, что флаг прыжка уже обработан и дальнейшая обработка не требуется

    public:

        RigidBodyStatus::E HandleNewGeometryContact(const GeometryContact *contact);

        bool	isPlayer;

        VehicleController(float azimuth);
        VehicleController(float azimuth, bool isPlayer);

        VehicleController();
        virtual ~VehicleController() override;

        static bool ValidNode(const Node *node);

        void Preprocess(void);
        void Move(void);

        void RotateWheel(Node *wheel);

        unsigned long GetMovementFlags(void) const //-V126
        {
            return (movementFlags);
        }

        void SetMovementFlags(unsigned long flags) //-V126
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

    };
}
