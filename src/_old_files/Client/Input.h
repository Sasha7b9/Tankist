#pragma once



namespace ActionType
{
    const Pi::ActionType::S CameraForward = 'frwd';
    const Pi::ActionType::S CameraBackward = 'bkwd';
    const Pi::ActionType::S CameraLeft = 'left';
    const Pi::ActionType::S CameraRight = 'rght';
    const Pi::ActionType::S CameraUp = 'jump';
    const Pi::ActionType::S CameraDown = 'down';
    const Pi::ActionType::S TankTowerLeft = 'Tlft';   ///< Поворот башни влево
    const Pi::ActionType::S TankTowerRight = 'Trth';   ///< Поворот башни вправо
    const Pi::ActionType::S TankForward = 'Tfrw';
    const Pi::ActionType::S TankBackward = 'Tbck';
    const Pi::ActionType::S TankLeft = 'Tlef';
    const Pi::ActionType::S TankRight = 'Trgh';
}



class CameraAction : public Action
{
private:
    uint movementFlag;
public:
    CameraAction(uint type, uint flag);
    ~CameraAction();

    void Begin();
    void End();
};



class TankAction : public Action
{
private:
    uint movementFlag;
public:
    TankAction(uint type, uint flag);
    ~TankAction();

    void Begin();
    void End();
};



class Input
{
public:

    static void Construct();
};
