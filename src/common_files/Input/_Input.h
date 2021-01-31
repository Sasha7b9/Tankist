#pragma once


using namespace Pi;


namespace Pi
{
    namespace ActionType
    {
        static const S Forward = 'frwd';
        static const S Backward = 'bkwd';
        static const S Left = 'left';
        static const S Right = 'rght';
        static const S Up = 'jump';
        static const S Down = 'down';
        static const S Fire = 'fire';
    }


    enum
    {
        kMovementForward   = 1 << 0,
        kMovementBackward  = 1 << 1,
        kMovementLeft      = 1 << 2,
        kMovementRight     = 1 << 3,
        kMovementUp        = 1 << 4,
        kMovementDown      = 1 << 5,
        kMovementPlanarMask = 15
    };
}

class MovementAction : public Action
{
private:

    unsigned long	movementFlag; //-V126

public:

    MovementAction(unsigned long type, unsigned long flag); //-V126
    ~MovementAction();

    void Begin(void);
    void End(void);
};
