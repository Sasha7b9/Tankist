#pragma once


namespace Urho3D
{
    class Node;
    class Scene;
}


class Logo;
class Vehicle;


class Battler : public Application
{
    URHO3D_OBJECT(Battler, Application);

public:
    /// Construct.
    explicit Battler(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

    void Setup() override;

    /// Cleanup after the main loop. Called by Application.
    void Stop() override;

private:

    /// Set custom window Title & Icon
    void SetWindowTitleAndIcon();

    /// Create static scene content.
    void CreateScene();

    /// Subscribe to necessary events.
    void SubscribeToEvents();

    /// The controllable vehicle component.
    WeakPtr<Vehicle> vehicle;

    WeakPtr<Logo> logo;


    /// Handle application update. Set controls to vehicle.
    void HandleUpdate(StringHash eventType, VariantMap &eventData);

    /// Handle application post-update. Update camera position after vehicle has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap &eventData);

    /// Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap &eventData);

    /// Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap &eventData);

    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap &eventData);
};
