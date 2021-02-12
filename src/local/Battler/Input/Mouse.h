#pragma once


class Mouse : public Object
{
    URHO3D_OBJECT(Mouse, Object);
public:

    Mouse(Context *context) : Object(context) { InitMode(MM_RELATIVE); }

    // Initialize mouse mode on non-web platform.
    void InitMode(MouseMode mode);

    int GetMoveX() const;
    int GetMoveY() const;

    MouseMode mode = MM_ABSOLUTE;        /// Mouse mode option to use in the sample.
};
