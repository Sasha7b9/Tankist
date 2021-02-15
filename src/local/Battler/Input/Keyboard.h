// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Keyboard : public IInput
{
    URHO3D_OBJECT(Keyboard, IInput);

public:

    Keyboard(Context *context);

    virtual ~Keyboard();

    bool GetKeyDown(Key key) const;
    bool GetKeyPress(Key key) const;

private:

    void SubscribeToEvents();

    // Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap &eventData);

    // Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap &eventData);
};
