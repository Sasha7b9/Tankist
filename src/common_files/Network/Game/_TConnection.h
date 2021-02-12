#pragma once


namespace Message
{
    struct GameMessage;
}


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(bool reliable, const Message::GameMessage &message) const;

    Connection *self = nullptr;
};
