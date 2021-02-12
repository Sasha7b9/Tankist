/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


Context          *TheContext = nullptr;
FileSystem       *TheFileSystem = nullptr;
Log              *TheLog = nullptr;
Network          *TheNetwork = nullptr;
ResourceCache    *TheCache = nullptr;
Time             *TheTime = nullptr;

Audio            *TheAudio = nullptr;
Console          *TheConsole = nullptr;
DebugHud         *TheDebugHud = nullptr;
DebugRenderer    *TheDebugRenderer = nullptr;
Graphics         *TheGraphics = nullptr;
Localization     *TheLocale = nullptr;
PhysicsWorld     *ThePhysicsWorld = nullptr;
Renderer         *TheRenderer = nullptr;
UI               *TheUI = nullptr;
UIElement        *TheUIRoot = nullptr;

String           TheIPAddress;
unsigned short   TheNumPort;
