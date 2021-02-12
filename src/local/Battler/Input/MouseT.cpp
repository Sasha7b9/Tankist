#include "stdafx.h"


void MouseT::InitMode(MouseMode m)
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


int MouseT::GetMoveX() const
{
    return TheInput->input->GetMouseMoveX();
}


int MouseT::GetMoveY() const
{
    return TheInput->input->GetMouseMoveY();
}
