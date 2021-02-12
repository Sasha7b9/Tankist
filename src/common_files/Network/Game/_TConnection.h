#pragma once


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}
    void SendMessage(int id, bool reliable, const DataNetwork &data)
    {
        if (self)
        {
            self->SendMessage(id, reliable, reliable, data.buffer);
        }
    }
    void SendMessage(int id, bool reliable, const VectorBuffer &buffer)
    {
        if (self)
        {
            self->SendMessage(id, reliable, reliable, buffer);
        }
    }
    Connection *self = nullptr;
};
