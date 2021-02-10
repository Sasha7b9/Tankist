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
};