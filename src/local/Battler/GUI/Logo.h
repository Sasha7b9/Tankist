// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Logo : public Object
{
    URHO3D_OBJECT(Logo, Object);
public:

    Logo(Context *conterxt);

    virtual ~Logo() {}

    /// Logo sprite.
    SharedPtr<Sprite> logoSprite_;
};
