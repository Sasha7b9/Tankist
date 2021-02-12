#pragma once


class IInput : public Object
{
    URHO3D_OBJECT(IInput, Object);

public:

    IInput(Context *context) : Object(context) { input = GetSubsystem<Input>(); }

protected:

    Input *input = nullptr;
};
