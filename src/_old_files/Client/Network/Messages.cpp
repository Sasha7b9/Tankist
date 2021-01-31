#include "stdafx.h"
#include "Network/Messages.h"
#include "globals.h"



MessageMovement::MessageMovement() : Message(MessageType::Movement)
{

}


MessageMovement::MessageMovement(uint _direction) : Message(MessageType::Movement),
    direction(_direction)
{
}


MessageMovement::~MessageMovement()
{

}


void MessageMovement::Compress(Compressor& data) const
{
    data << direction;
}


bool MessageMovement::Decompress(Decompressor &data)
{
    data >> direction;

    return true;
}


bool MessageMovement::HandleMessage(Player *sender) const
{
    if (PiHEADLESS)
    {
        sender->SendMessage(*this);

        return true;
    }
    else
    {
        /*
        if (TheTank)
        {
            if (direction & (1 << 31))
            {
                TheTank->GetController()->RemoveMovementFlag(direction ^ (1 << 31));
            }
            else
            {
                TheTank->GetController()->AddMovementFlag(direction);
            }
        }
        */

        return true;
    }
}



MessageReplicate::MessageReplicate() : Message(MessageType::Replicate)
{

}


MessageReplicate::MessageReplicate(Pi::Point3D _position, Pi::String<> _nameNode) : Message(MessageType::Replicate),
    position(_position),
    nameNode(_nameNode)
{

}


MessageReplicate::~MessageReplicate()
{

}


void MessageReplicate::Compress(Pi::Compressor& data) const
{
    data << position;
    data << nameNode;
}


bool MessageReplicate::Decompress(Pi::Decompressor &data)
{
    data >> position;
    data >> nameNode;

    return true;
}


bool MessageReplicate::HandleMessage(Pi::Player *) const
{
    if (PiHEADLESS)
    {

    }
    else
    {
        /*
        TheTank = Tank::Create();
        TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(TheTank->GetModel());
        TheTank->GetController()->GetTargetNode()->SetNodePosition(position);
        TheTank->GetController()->GetTargetNode()->SetNodeName(nameNode.c_str());
        */

        return true;
    }

    return false;
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
