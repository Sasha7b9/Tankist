#pragma once


struct Message;


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(int id, bool reliable, const VectorBuffer &buffer) const;

    void SendMessage(bool reliable, const Message &message) const;

    Connection *self = nullptr;
};
