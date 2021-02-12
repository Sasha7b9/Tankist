#include "stdafx.h"


namespace Message
{
    void GameMessage::Handle(VariantMap &map)
    {
        TConnection connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        if (id == MSG_TEXTSTRING)
        {
            ((TextString *)this)->Handle(msg);

        }

#ifdef CLIENT

        else if (id == MSG_BUILD_SCENE)
        {
            ((BuildScene *)this)->Handle(msg);
        }

#elif defined SERVER

        else if (id == MSG_REQUEST_FOR_BUILD_SCENE)
        {
            ((RequestForBuildScene *)this)->Handle(connection);
        }
        else if (id == MSG_KEY_EVENT)
        {
            //        ((KeyEvent *)this)->Handle(msg);
        }

#endif
    }

}
