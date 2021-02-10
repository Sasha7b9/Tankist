#pragma once



class DropDownListButtons : public Object
{
    URHO3D_OBJECT(DropDownListButtons, Object)

public:
    DropDownListButtons(Context *context, UIElement *parent, const char *nameDDLB);

    void AddItem(const String &item);

    uint CurrentItem(String &item);

    void SetCurrentItem(const String &item);

private:

    DropDownListButtons(DropDownListButtons const&) : Object(nullptr) {};
    DropDownListButtons operator=(DropDownListButtons const&) { return *this; };


    DropDownList *list;

    void HandleButtonLess(StringHash, VariantMap&);

    void HandleButtonMore(StringHash, VariantMap&);
};
