#pragma once
#include "Battler.h"
//#include "Objects/CameraUni.h"
#include "Network/Client.h"
#include "Network/Chat.h"
#include "Network/Server.h"
#include "Game.h"
#include "Network/ChatLog.h"
//#include "Audio/AudioCapturer.h"
#include "GUI/WindowGameESC.h"
#include "GUI/WindowSettings.h"
#include "Settings.h"
#include "Counters.h"
#include "GUI/GameGUI.h"
#include <Urho3D/UI/UI.h>


// ����� ���������� ��� ������� � �������
// ���������� ��������
extern Context *TheContext;
// ���������� ������������
extern Log *TheLog;
// ��� ����
extern ChatLog *TheChatLog;
// ������� �������
extern Network *TheNetwork;
// ���������� ��� ������ � �������� �������
extern FileSystem *TheFileSystem;
// ���������� �������� � �����������
extern ResourceCache *TheCache;
// ��������� �� �������� ������� �����
extern Scene *TheScene;
// ��������� �������
extern Time *TheTime;
// ������
extern Server *TheServer;
// ��� ���������� - ������ ��� ������
extern TypeApplication TheTypeApplication;
// ��������� ���   
extern Chat *TheChat;


// ���������� ��� �������
// ��������� �� ����������� ����������
extern UI *TheUI;
// �������� ������� ��� (����������� ��������� ������������ - GUI)
extern UIElement *TheUIRoot;
// ��������� �� ���������� �����
extern Input *TheInput;
// ��������� �� ������
extern Renderer *TheRenderer;
// ��������� �� ����������� ����������
extern Graphics *TheGraphics;
// �������
extern Console *TheConsole;
// ���������� ���������
extern DebugHud *TheDebugHud;
// �������� ����������
extern Audio *TheAudio;
// ������ ����� � ���������
//extern AudioCapturer *TheAudioCapturer;
// ���������� �����������
extern Localization *TheLocale;
// ���������� ����������� �������
extern DebugRenderer *TheDebugRenderer;
// ���������� ���������� ���������
extern PhysicsWorld *ThePhysicsWorld;
// ������� ������
//extern CameraUni *TheCamera;
// ������� ������ ��� ����� �� ����
extern Client *TheClient;
// ������� ���
extern GameGUI *TheGameGUI;
// ����, ������������� � ���� �� ������� ������� Esc
extern WindowGameESC *TheWindowGameESC;

extern String  TheIPAddress;
extern unsigned short TheNumPort;

extern Battler *TheTankist;
extern Game *TheGame;
extern WindowSettings *TheWindowSettings;
extern Settings *TheSet;
extern Counters *TheCounters;
