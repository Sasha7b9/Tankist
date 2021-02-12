#include "stdafx.h"


void MessageRequestForBuildScene::Handle(const TConnection &connection)
{
    connection.SendMessage(true, MessageBuildScene({ 10.0f, 10.0f, 10.0f }));
}
