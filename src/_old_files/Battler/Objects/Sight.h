#pragma once



class Sight : public Window
{
    URHO3D_OBJECT(Sight, Window);

public:
    Sight(Context *context);

private:
    Sight(Sight const&) : Window(nullptr) {};
    Sight operator=(Sight const&) { return *this; };
};
