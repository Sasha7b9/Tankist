#pragma once


class IInput : public Object
{
    URHO3D_OBJECT(IInput, Object);

public:

    IInput(Context *context);

protected:

    Input *input = nullptr;
};
