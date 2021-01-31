#include "stdafx.h"


void Server::HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &, const void *)
{
    switch (event)
    {
    case ConnectionEvent::AttemptFailed:
        break;

    case ConnectionEvent::ClientOpened:
        break;

    case ConnectionEvent::ServerAccepted:
        break;

    case ConnectionEvent::ServerClosed:
        break;

    case ConnectionEvent::ClientClosed:
        break;

    case ConnectionEvent::ServerTimedOut:
        break;

    case ConnectionEvent::ClientTimedOut:
        break;

    case ConnectionEvent::QueryReceived:
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


Message *Server::CreateMessage(MessageType::E type, Decompressor &) const //-V2506
{
    switch (type)
    {
    case MessageType::Movement:
        return new MovementMessage(); //-V2511
        break;

    case MessageType::ServerPing:
        return new ServerPingMessage(); //-V2511
        break;

    case MessageType::RespawnRequest:
        return new RespawnRequestMessage(); //-V2511
        break;

    case MessageType::RespawnDo:
        return new RespawnDoMessage(); //-V2511
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }

    return nullptr;
}


void Server::ReceiveMessage(Player *player, const NetworkAddress &, const Message *message) //-V2558
{
    switch(message->GetMessageType())
    {
    case MessageType::Movement:
        {
            GamePlayer *p = players.First();

            while(p)
            {
                if(p->key == player->GetPlayerKey())
                {
                    VehicleController *controller = p->controller;

                    const MovementMessage *movement = static_cast<const MovementMessage *>(message);

                    if(movement->begin)
                    {
                        controller->SetMovementFlags(controller->GetMovementFlags() | movement->direction);
                    }
                    else
                    {
                        controller->SetMovementFlags(controller->GetMovementFlags() & ~movement->direction);
                    }

                    break;
                }

                p = p->Next();
            }
            
        }
        break;

    case MessageType::ServerPing:
        TheMessageMgr->SendMessage(player->GetKey(), *message);
        break;

    case MessageType::RespawnRequest:
        {
            Point3D location;
            location.x = 0.0F;
            location.y = 0.0F;
            location.z = 2.0F;
            int index = TheWorldMgr->GetWorld()->NewControllerIndex();
            TheMessageMgr->SendMessageAll(RespawnDoMessage(player->GetPlayerKey(), location, index));
        }
        break;

    case MessageType::RespawnDo:
        CreateNewPlayer(static_cast<const RespawnDoMessage *>(message));
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


void Server::HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *) //-V2558
{
    switch (event)
    {
    case PlayerEvent::Connected:
        break;

    case PlayerEvent::Disconnected:
    case PlayerEvent::TimedOut:
        {
            GamePlayer *p = players.First();
            while(p)
            {
                if(p->key == player->GetPlayerKey())
                {
                    p->controller->GetTargetNode()->Disable();
                    TheWorldMgr->GetWorld()->GetRootNode()->RemoveSubnode(p->controller->GetTargetNode());
                    delete p->controller; //-V2511
                    players.Remove(p);
                    break;
                }

                p = p->Next();
            }
        }

        TheMessageMgr->SendMessageClients(RemovePlayerMessage(player->GetPlayerKey()));

        break;

    case PlayerEvent::Initialized:
        // Сюда мы попадаем при инициализации нового игрока. И мы должны передать ему информацию о всех объектах, которых нет в исходном мире
        {
            GamePlayer *p = players.First();

            while(p)
            {
                VehicleController *controller = p->controller;

                if(controller)
                {
                    Node *node = controller->GetTargetNode();
                    PlayerKey key = p->key;
                    int id = controller->GetControllerIndex();
                    Point3D location = node->GetWorldPosition();

                    TheMessageMgr->SendMessage(player->GetPlayerKey(), RespawnDoMessage(key, location, id));
                }

                p = p->Next();
            }
        }
        break;

    case PlayerEvent::ChatReceived:
        break;

    case PlayerEvent::Renamed:
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}


void Server::HandleGameEvent(GameEvent event, const void *)
{
    switch (event) //-V785
    {
    case kGameSynchronized:
        break;

    default:
        PiLOG_DEFAULT_CASE;
        break;
    }
}
