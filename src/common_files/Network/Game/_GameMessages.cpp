#include "stdafx.h"


void Message::Handle(VariantMap &map)
{
    TConnection connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

    MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

    if (id == MSG_TEXTSTRING)
    {
        ((MessageTextString *)this)->Handle(msg);

    }

#ifdef CLIENT

    else if(id == MSG_BUILD_SCENE)
    {
        ((MessageBuildScene *)this)->Handle(msg);
    }

#elif defined SERVER

    else if (id == MSG_REQUEST_FOR_BUILD_SCENE)
    {
        ((MessageRequestForBuildScene *)this)->Handle(connection);
    }
    else if (id == MSG_KEY_EVENT)
    {
//        ((MessageKeyEvent *)this)->Handle(msg);
    }

#endif
}
