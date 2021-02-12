#pragma once


class GameInput : public Object
{

    URHO3D_OBJECT(GameInput, Object);

public:

    GameInput(Context *context);

private:

    void SubscribeToEvents();

    // Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap &eventData);

    // Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap &eventData);
};
