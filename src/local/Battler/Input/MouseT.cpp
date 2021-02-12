#include "stdafx.h"


void Mouse::InitMode(MouseMode m)
{
    mode = m;

    if (mode == MM_FREE)
    {
        TheInput->input->SetMouseVisible(true);
    }

    if (mode != MM_ABSOLUTE)
    {
        TheInput->input->SetMouseMode(mode);
        if (TheConsole && TheConsole->IsVisible())
        {
            TheInput->input->SetMouseMode(MM_ABSOLUTE, true);
        }
    }
}


int Mouse::GetMoveX() const
{
    return TheInput->input->GetMouseMoveX();
}


int Mouse::GetMoveY() const
{
    return TheInput->input->GetMouseMoveY();
}
