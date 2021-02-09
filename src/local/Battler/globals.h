#pragma once
#include "Battler.h"
#include "Objects/CameraUni.h"
#include "Network/Client.h"
#include "Network/Chat.h"
#include "Network/Server.h"
#include "Game.h"
#include "Network/ChatLog.h"
#include "Audio/AudioCapturer.h"
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
extern UI *gUI;
// �������� ������� ��� (����������� ��������� ������������ - GUI)
extern UIElement *gUIRoot;
// ��������� �� ���������� �����
extern Input *gInput;
// ��������� �� ������
extern Renderer *gRenderer;
// ��������� �� ����������� ����������
extern Graphics *gGraphics;
// �������
extern Console *gConsole;
// ���������� ���������
extern DebugHud *gDebugHud;
// �������� ����������
extern Audio *gAudio;
// ������ ����� � ���������
extern AudioCapturer *gAudioCapturer;
// ���������� �����������
extern Localization *gLocale;
// ���������� ����������� �������
extern DebugRenderer *gDebugRenderer;
// ���������� ���������� ���������
extern PhysicsWorld *gPhysicsWorld;
// ������� ������
extern CameraUni *gCamera;
// ������� ������ ��� ����� �� ����
extern Client *gClient;
// ������� ���
extern GameGUI *gGameGUI;
// ����, ������������� � ���� �� ������� ������� Esc
extern WindowGameESC *gWindowGameESC;

extern String  gIPAddress;
extern unsigned short gNumPort;

extern Battler *gTankist;
extern Game *gGame;
extern WindowSettings *gWindowSettings;
extern Settings *gSet;
extern Counters *gCounters;
