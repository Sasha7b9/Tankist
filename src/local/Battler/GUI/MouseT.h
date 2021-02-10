#pragma once


class MouseT : public Object
{
    URHO3D_OBJECT(MouseT, Object);
public:

    MouseT(Context *context) : Object(context) { InitMode(MM_RELATIVE); }

    /// Initialize mouse mode on non-web platform.
    void InitMode(MouseMode mode);

    MouseMode mode = MM_ABSOLUTE;        /// Mouse mode option to use in the sample.
};
