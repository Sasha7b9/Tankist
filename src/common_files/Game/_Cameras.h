#pragma once


using namespace Pi;


/// ����� ChaseCamera ������������ ������, ������� ����� ����������� �������� ������.
class ChaseCamera : public FrustumCamera
{
public:

    ChaseCamera();
    ~ChaseCamera();

    Model *GetTargetModel(void) const
    {
        return (targetModel);
    }

    void SetTargetModel(Model *model)
    {
        targetModel = model;
    }

    void Move(void);

private:

    Model *targetModel; //-V122

    float distance = 1.0F;

};