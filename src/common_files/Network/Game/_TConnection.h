#pragma once


class HeadConnection
{
public:
    HeadConnection(Connection *connection) : self(connection) {}
    void SendMessage(int id, bool reliable, const DataNetwork &data)
    {
        self->SendMessage(id, reliable, reliable, data.buffer);
    }
    Connection *self = nullptr;
};
