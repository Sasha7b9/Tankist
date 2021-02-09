/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */

#ifdef WIN32

#include "TWTThreads.h"



Signal::Signal(int count)
{
    signalCount = count;

    for (int a = 0; a < count; a++)
    {
        signalEvent[a] = CreateEventA(nullptr, false, false, nullptr);
    }
}

#endif

