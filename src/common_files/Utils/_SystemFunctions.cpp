#include "stdafx.h"


#ifdef WIN32

void win::SetConsoleCP(uint cp)
{
    if (!::SetConsoleCP(cp))
    {
        DISPLAY_LAST_ERROR();
    }
}

#endif
