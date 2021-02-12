#include "stdafx.h"


void Message::Handle(MemoryBuffer &msg)
{
    if (id == MSG_TEXTSTRING)
    {
        ((MessageTextString *)this)->Handle(msg);

    }
}
