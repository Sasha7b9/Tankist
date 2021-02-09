/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "globals.h"


// For server and client
Log *TheLog = nullptr;
Network *TheNetwork = nullptr;
FileSystem *TheFileSystem = nullptr;
ResourceCache *TheCache = nullptr;
Scene *TheScene = nullptr;
Time *TheTime = nullptr;

Server *TheServer = nullptr;
TypeApplication TheTypeApplication = Type_None;


// For client only
UI *gUI = nullptr;
UIElement *gUIRoot = nullptr;
Input *gInput = nullptr;
Renderer *gRenderer = nullptr;
Graphics *gGraphics = nullptr;
Console *gConsole = nullptr;
DebugHud *gDebugHud = nullptr;
Audio *gAudio = nullptr;
Localization *gLocale = nullptr;
DebugRenderer *gDebugRenderer = nullptr;
PhysicsWorld *gPhysicsWorld = nullptr;

CameraUni *gCamera = nullptr;
Client *gClient = nullptr;

String gIPAddress = "";
unsigned short gNumPort = 0;

Context *TheContext = nullptr;

Battler *gTankist = nullptr;
Chat *TheChat = nullptr;
Game *gGame = nullptr;
ChatLog *TheChatLog = nullptr;
AudioCapturer *gAudioCapturer = nullptr;
WindowGameESC *gWindowGameESC = nullptr;
WindowSettings *gWindowSettings = nullptr;
Settings *gSet = nullptr;
Counters *gCounters = nullptr;
GameGUI *gGameGUI = nullptr;
