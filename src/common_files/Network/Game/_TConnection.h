#pragma once


namespace Message
{
    struct Message;
}


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(bool reliable, const Message::Message &message) const;

    Connection *self = nullptr;
};
