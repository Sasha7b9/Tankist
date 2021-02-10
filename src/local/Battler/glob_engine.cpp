/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "glob_engine.h"


// For server and client
Log *TheLog = nullptr;
Network *TheNetwork = nullptr;
FileSystem *TheFileSystem = nullptr;
ResourceCache *TheCache = nullptr;
Scene *TheScene = nullptr;
Time *TheTime = nullptr;

//Server *TheServer = nullptr;
//TypeApplication TheTypeApplication = Type_None;


// For client only
UI *TheUI = nullptr;
UIElement *TheUIRoot = nullptr;
Input *TheInput = nullptr;
Renderer *TheRenderer = nullptr;
Graphics *TheGraphics = nullptr;
Console *TheConsole = nullptr;
DebugHud *TheDebugHud = nullptr;
Audio *TheAudio = nullptr;
Localization *TheLocale = nullptr;
DebugRenderer *TheDebugRenderer = nullptr;
PhysicsWorld *ThePhysicsWorld = nullptr;

//CameraUni *TheCamera = nullptr;
//Client *TheClient = nullptr;

String TheIPAddress = "";
unsigned short TheNumPort = 0;

Context *TheContext = nullptr;

//Battler *TheTankist = nullptr;
//Chat *TheChat = nullptr;
//Game *TheGame = nullptr;
//ChatLog *TheChatLog = nullptr;
//AudioCapturer *TheAudioCapturer = nullptr;
//WindowGameESC *TheWindowGameESC = nullptr;
//WindowSettings *TheWindowSettings = nullptr;
//Settings *TheSet = nullptr;
//Counters *TheCounters = nullptr;
//GameGUI *TheGameGUI = nullptr;
