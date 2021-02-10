#include "stdafx.h"


void MouseT::InitMode(MouseMode m)
{
    mode = m;

    if (mode == MM_FREE)
        TheInput->SetMouseVisible(true);

    if (mode != MM_ABSOLUTE)
    {
        TheInput->SetMouseMode(mode);
        if (TheConsole && TheConsole->IsVisible())
            TheInput->SetMouseMode(MM_ABSOLUTE, true);
    }
}
