#include "stdafx.h"


uint ServerPingMessage::lastMessage = 0;


MovementMessage::MovementMessage() : Message(MessageType::Movement)
{

}


MovementMessage::MovementMessage(uint _direction, bool _begin) : Message(MessageType::Movement),
    direction(_direction),
    begin(_begin)
{
}


MovementMessage::~MovementMessage()
{

}


void MovementMessage::Compress(Compressor& data) const
{
    data << direction;
    data << begin;
}


bool MovementMessage::Decompress(Decompressor &data)
{
    data >> direction;
    data >> begin;

    return true;
}


RespawnDoMessage::RespawnDoMessage() : Message(MessageType::RespawnDo)
{

}


RespawnDoMessage::RespawnDoMessage(PlayerKey _key, Point3D _position, int _index) : Message(MessageType::RespawnDo),
    position(_position),
    index(_index),
    key(_key)
{

}


void RespawnDoMessage::Compress(Compressor& data) const
{
    data << position;
    data << index;
    data << key;
}


bool RespawnDoMessage::Decompress(Decompressor &data)
{
    data >> position;
    data >> index;
    data >> key;

    return true;
}


void RemovePlayerMessage::Compress(Compressor &data) const
{
    data << key;
}

bool RemovePlayerMessage::Decompress(Decompressor &data)
{
    data >> key;

    return true;
}


MessageTankInfo::MessageTankInfo() : Message(MessageType::TankInfo)
{

}


MessageTankInfo::MessageTankInfo(Pi::Point3D _position, Pi::String<> _nameNode, bool _create) : Message(MessageType::TankInfo),
    position(_position),
    nameNode(_nameNode),
    create(_create)
{

}


MessageTankInfo::~MessageTankInfo()
{

}


void MessageTankInfo::Compress(Pi::Compressor& data) const
{
    data << position;
    data << nameNode;
    data << create;
}


bool MessageTankInfo::Decompress(Pi::Decompressor &data)
{
    data >> position;
    data >> nameNode;
    data >> create;

    return true;
}


bool MessageTankInfo::HandleMessage(Pi::Player *) const
{
    if (PiHEADLESS)
    {

    }
    else
    {
        /*
        if (create)
        {
            Tank *tank = Tank::Create();
            TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(tank->GetModel());
            tank->GetController()->GetTargetNode()->SetNodePosition(position);
            tank->GetController()->GetTargetNode()->SetNodeName(nameNode.c_str());
        }
        */
    }

    return false;
}


ServerPingMessage::ServerPingMessage() : Message(MessageType::ServerPing)
{
    if(!TheMessageMgr->IsServer())
    {
        numberMessage = lastMessage++;
        timeSend = TheTimeMgr->GetSystemAbsoluteTime();
    }
}


void ServerPingMessage::Compress(Compressor &data) const
{
    data << timeSend;
    data << numberMessage;
}


bool ServerPingMessage::Decompress(Decompressor &data)
{
    data >> timeSend;
    data >> numberMessage;

    return true;
}


int ServerPingMessage::GetPing() const
{
    int ping = static_cast<int>(TheTimeMgr->GetSystemAbsoluteTime() - timeSend);

    return ping;
}


ServerInfoMessage::ServerInfoMessage(uint *pIn, uint *pOut) : Message(MessageType::ServerInfo)
{
    fps = TheEngine->GetFPS();
    count = TheMessageMgr->GetPlayerCount() - 1;
    sendedBytes = TheNetworkMgr->GetBytesSend();
    receivedBytes = TheNetworkMgr->GetBytesRecv();

    speedIn = pIn ? *pIn : 0;
    speedOut = pOut ? *pOut : 0;
}


void ServerInfoMessage::Compress(Compressor &data) const
{
    data << fps;
    data << count;
    data << sendedBytes;
    data << receivedBytes;
    data << speedIn;
    data << speedOut;
}


bool ServerInfoMessage::Decompress(Decompressor &data)
{
    data >> fps;
    data >> count;
    data >> sendedBytes;
    data >> receivedBytes;
    data >> speedIn;
    data >> speedOut;

    return true;
}
