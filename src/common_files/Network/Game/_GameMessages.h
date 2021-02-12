#pragma once
#include "_GameMessagesID.h"


struct Message
{
    Message(int _id) : id(_id) {}
    void Handle(VariantMap &map);
    int id;
    VectorBuffer buffer;

#ifdef CLIENT
    void Send(bool reliable);           // Метод действителен только для клиента. Серверу нужно ещё знать, в какое сое-
                                        // нение засылать
#endif
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

    void Handle(MemoryBuffer &msg);
};


                                                 // Запрос на построение сцены. Выполняется клиентом после инициализации
struct MessageRequestForBuildScene : public Message
{
    MessageRequestForBuildScene() : Message(MSG_REQUEST_FOR_BUILD_SCENE) {}

    void Handle(const TConnection &connection);
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
