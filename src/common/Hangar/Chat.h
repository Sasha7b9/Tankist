#pragma once


using namespace Pi;


class ChatMessage : public ListElement<ChatMessage>
{
public:
    ChatMessage(pchar message);
    
    String<1024> message;
    DateTime     dateTime;
};


class PlayerStruct : public MapElement<PlayerStruct>
{
public:

    typedef PlayerKey KeyType;

    PlayerStruct(Player *_player) : player(_player) {};
    int sended = 0;
    Player *player = nullptr; //-V122

    KeyType GetKey() const { return player->GetKey(); }
};


class Chat : public Singleton<Chat>
{
public:
    static void Create();
    void AddMessage(pchar  message);
private:
    Chat();
    List<ChatMessage> history;      ///< Здесь хранится история сообщений
    Map<PlayerStruct> players;      ///< Список обрабатываемых игроков
    // Послать numMessages последних сообщений игроку
    void SendMessages(PlayerStruct *str);
};
