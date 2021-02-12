#pragma once


struct Message;


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(bool reliable, const Message &message) const;

    Connection *self = nullptr;
};
