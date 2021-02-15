// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Mouse : public IInput
{
    URHO3D_OBJECT(Mouse, IInput);
public:

    Mouse(Context *context) : IInput(context) { InitMode(MM_RELATIVE); }

    // Initialize mouse mode on non-web platform.
    void InitMode(MouseMode mode);

    int GetMoveX() const;
    int GetMoveY() const;

    MouseMode mode = MM_ABSOLUTE;        /// Mouse mode option to use in the sample.
};
