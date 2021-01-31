#pragma once

class GameGUI
{
public:
    GameGUI();
    static void AddSystemMessage(const char *text);
    static void SetPing(int ping);
};
