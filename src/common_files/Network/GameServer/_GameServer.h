#pragma once


class GameServer : public Object
{
    URHO3D_OBJECT(GameServer, Object);

public:

    GameServer(Context *context) : Object(context) {}


    // ������������ � ����� ��� �������������
    virtual bool Start(uint16 port) { (void)port; return false; };
};
