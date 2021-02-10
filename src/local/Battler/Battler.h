#pragma once

namespace Urho3D
{
    class Node;
    class Scene;
}

class Vehicle;

/// Vehicle example.
/// This sample demonstrates:
///     - Creating a heightmap terrain with collision
///     - Constructing 100 raycast vehicles
///     - Defining attributes (including node and component references) of a custom component
///     (Saving and loading is broken now)

class Battler : public Application
{
    URHO3D_OBJECT(Battler, Application);

public:
    /// Construct.
    explicit Battler(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

    void Setup() override;

private:

    /// Create logo.
    void CreateLogo();

    /// Set custom window Title & Icon
    void SetWindowTitleAndIcon();

    /// Create console and debug HUD.
    void CreateConsoleAndDebugHud();

    /// Create static scene content.
    void CreateScene();

    /// Create the vehicle.
    void CreateVehicle();

    /// Construct an instruction text to the UI.
    void CreateInstructions();

    /// Subscribe to necessary events.
    void SubscribeToEvents();

    /// Initialize mouse mode on non-web platform.
    void InitMouseMode(MouseMode mode);

    /// Handle application update. Set controls to vehicle.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Handle application post-update. Update camera position after vehicle has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Handle key down event to process key controls common to all samples.
    void HandleKeyDown(StringHash eventType, VariantMap &eventData);

    /// Handle key up event to process key controls common to all samples.
    void HandleKeyUp(StringHash eventType, VariantMap &eventData);

    /// Handle request for mouse mode on web platform.
    void HandleMouseModeRequest(StringHash eventType, VariantMap &eventData);

    /// Handle request for mouse mode change on web platform.
    void HandleMouseModeChange(StringHash eventType, VariantMap &eventData);

    /// Handle scene update event to control camera's pitch and yaw for all samples.
    void HandleSceneUpdate(StringHash eventType, VariantMap &eventData);

    /// The controllable vehicle component.
    WeakPtr<Vehicle> vehicle_;

    /// Scene.
    SharedPtr<Scene> scene_;

    /// Camera scene node.
    SharedPtr<Node> cameraNode_;

    /// Logo sprite.
    SharedPtr<Sprite> logoSprite_;

    /// Mouse mode option to use in the sample.
    MouseMode useMouseMode_;
};
