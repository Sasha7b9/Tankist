#pragma once


namespace MessageType
{
    enum : Pi::MessageType::E
    {
        Movement = Pi::MessageType::BaseCount,    ///< Управление
        Replicate,                                ///< Респаун
        TankInfo                                  ///< Используется для передачи клиентам информации о других игроках
    };
}



class MessageMovement : public Pi::Message
{
    friend class Tankist;

public:
    MessageMovement(uint direction);
    ~MessageMovement();

    virtual void Compress(Pi::Compressor& data) const override;
    virtual bool Decompress(Pi::Decompressor &data) override;

    virtual bool HandleMessage(Pi::Player *sender) const override;

private:
    MessageMovement();

    uint direction = 0;
};



class MessageReplicate : public Pi::Message
{
    friend class Tankist;

public:
    MessageReplicate(Pi::Point3D position, Pi::String<> nameNode);
    ~MessageReplicate();

    virtual void Compress(Pi::Compressor& data) const override;
    virtual bool Decompress(Pi::Decompressor &data);

    virtual bool HandleMessage(Pi::Player *sender) const override;

private:
    MessageReplicate();

    Pi::Point3D position;
    Pi::String<> nameNode;
};



class MessageTankInfo : public Pi::Message
{
    friend class Tankist;

public:
    MessageTankInfo(Pi::Point3D position, Pi::String<> nameNode, bool create);
    ~MessageTankInfo();

    virtual void Compress(Pi::Compressor& data) const override;
    virtual bool Decompress(Pi::Decompressor &data);

    virtual bool HandleMessage(Pi::Player *sender) const override;

private:
    MessageTankInfo();

    Pi::Point3D position;
    Pi::String<> nameNode;
    bool create = false;    ///< true означает, что передаётся информация о новом узле, который нужно создать и вставить в сцену
};
