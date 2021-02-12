#include "stdafx.h"


void GMessage::RequestForBuildScene::Handle(const TConnection &connection)
{
    connection.SendMessage(true, GMessage::BuildScene({ 10.0f, 10.0f, 10.0f }));
}
