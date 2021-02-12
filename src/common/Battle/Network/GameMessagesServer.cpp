#include "stdafx.h"


void Message::RequestForBuildScene::Handle(const TConnection &connection)
{
    connection.SendMessage(true, Message::BuildScene({ 10.0f, 10.0f, 10.0f }));
}
