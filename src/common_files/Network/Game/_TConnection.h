#pragma once


namespace GMessage
{
    struct GameMessage;
}


class TConnection
{
public:
    TConnection(Connection *connection) : self(connection) {}

    void SendMessage(bool reliable, const GMessage::GameMessage &message) const;

    Connection *self = nullptr;
};
