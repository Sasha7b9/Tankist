#pragma once



class ChaseCamera : public Pi::FrustumCamera
{
private:

    Model *targetModel;

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
};
