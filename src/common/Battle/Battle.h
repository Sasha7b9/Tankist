/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class Battle : public Application
{
    URHO3D_OBJECT(Battle, Application);

public:

    explicit Battle(Context *context);

    virtual void Start() override;

    virtual void Setup() override;

    virtual void Stop() override;

    void Exit();

private:

    void SubscribeToEvents();

    // Handle application update. Set controls to vehicle.
    void HandleUpdate(StringHash eventType, VariantMap &eventData);

    // Handle application post-update. Update camera position after vehicle has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap &eventData);
};