#include "stdafx.h"


void Message::Handle(VariantMap &map)
{
    TConnection connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

    MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

    if (id == MSG_TEXTSTRING)
    {
        ((MessageTextString *)this)->Handle(msg);

    }
    else if (id == MSG_SCENE_REQUEST_FOR_BUILD)
    {
        ((MessageRequestForBuildScene *)this)->Handle(connection);
    }
    //else if (id == MSG_SCENE_BUILD)
    //{
    //    ((MessageBuildScene *)this)->Handle(connection, msg);
    //}
}
