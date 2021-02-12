#pragma once
#include "_GameMessagesID.h"


struct Message
{
    Message(int _id) : id(_id) {}
    void Handle(VariantMap &map);
    int id;
    VectorBuffer buffer;
};


                                                                               // По этому сообщению клиент стрОит сцену
struct MessageBuildScene : public Message
{
    MessageBuildScene(
        const Vector3 &position             // позиция созданной сущности клиента
    ) :
        Message(MSG_SCENE_BUILD)
    {
        buffer.WriteVector3(position);
    }

    //    void Handle(const Connection &connection, MemoryBuffer &)
    //    {
    //        connection.SendMessage(true, MessageBuildScene)
    //    }
};


                                                 // Запрос на построение сцены. Выполняется клиентом после инициализации
struct MessageRequestForBuildScene : public Message
{
    MessageRequestForBuildScene() : Message(MSG_SCENE_REQUEST_FOR_BUILD) {}

    void Handle(const TConnection &connection)
    {
        connection.SendMessage(true, MessageBuildScene({ 10.0f, 10.0f, 10.0f }));
    }
};


                                                                                            // Передача текстовой строки
struct MessageTextString : public Message
{
    MessageTextString(const String &message) : Message(MSG_TEXTSTRING)
    {
        buffer.WriteString(message);
    }

    void Handle(MemoryBuffer &msg)
    {
        URHO3D_LOGINFO(msg.ReadString());
    }
};
