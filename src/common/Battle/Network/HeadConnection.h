#pragma once


class HeadConnection
{
public:
    HeadConnection(Connection *conn) : connection(conn) {}
    void SendMessage(int id, bool reliable, const DataNetwork &data)
    {
        connection->SendMessage(id, reliable, reliable, data.buffer);
    }
    Connection *connection = nullptr;
};
