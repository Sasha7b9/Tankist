/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class Logo;
class Vehicle;


class Battler : public Application
{
    URHO3D_OBJECT(Battler, Application);

public:
    // Construct.
    explicit Battler(Context* context);

    // Setup after engine initialization and before running the main loop.
    virtual void Start() override;

    virtual void Setup() override;

    // Cleanup after the main loop. Called by Application.
    virtual void Stop() override;

    void Exit();

private:

    // Set custom window Title & Icon
    void SetWindowTitleAndIcon();

    // Subscribe to necessary events.
    void SubscribeToEvents();

    WeakPtr<Logo> logo;

    // Handle application update. Set controls to vehicle.
    void HandleUpdate(StringHash eventType, VariantMap &eventData);

    // Handle application post-update. Update camera position after vehicle has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap &eventData);

    // Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap &eventData);
};
