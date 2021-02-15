// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void Mouse::InitMode(MouseMode m)
{
    mode = m;

    if (mode == MM_FREE)
    {
        input->SetMouseVisible(true);
    }

    if (mode != MM_ABSOLUTE)
    {
        input->SetMouseMode(mode);
        if (TheConsole && TheConsole->IsVisible())
        {
            input->SetMouseMode(MM_ABSOLUTE, true);
        }
    }
}


int Mouse::GetMoveX() const
{
    return input->GetMouseMoveX();
}


int Mouse::GetMoveY() const
{
    return input->GetMouseMoveY();
}
