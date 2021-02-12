#include "stdafx.h"


void TConnection::SendMessage(bool reliable, const Message::GameMessage &message) const
{
    if (self)
    {
        self->SendMessage(message.id, reliable, reliable, message.buffer);
    }
}
