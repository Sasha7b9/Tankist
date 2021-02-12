#pragma once


class GameInput : public IInput
{
    URHO3D_OBJECT(GameInput, IInput);

public:

    GameInput(Context *context);

    virtual ~GameInput();

    bool GetKeyDown(Key key) const;
    bool GetKeyPress(Key key) const;

private:

    void SubscribeToEvents();

    // Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap &eventData);

    // Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap &eventData);
};
