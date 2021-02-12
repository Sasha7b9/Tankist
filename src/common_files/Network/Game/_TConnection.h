#pragma once


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(int id, bool reliable, const VectorBuffer &buffer)
    {
        if (self)
        {
            self->SendMessage(id, reliable, reliable, buffer);
        }
    }

    void SendMessage(bool reliable, const Message &message)
    {
        if (self)
        {
            self->SendMessage(message.id, reliable, reliable, message.buffer);
        }
    }

    Connection *self = nullptr;
};
