#include "stdafx.h"


void TConnection::SendMessage(int id, bool reliable, const VectorBuffer &buffer) const
{
    if (self)
    {
        self->SendMessage(id, reliable, reliable, buffer);
    }
}

void TConnection::SendMessage(bool reliable, const Message &message) const
{
    if (self)
    {
        self->SendMessage(message.id, reliable, reliable, message.buffer);
    }
}
