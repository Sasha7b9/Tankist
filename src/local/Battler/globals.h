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


// Общие переменные для сервера и клиента
// Глобальный контекст
extern Context *TheContext;
// Подсистема логгирования
extern Log *TheLog;
// Лог чата
extern ChatLog *TheChatLog;
// Сетевая система
extern Network *TheNetwork;
// Подсистема для работы с файловой системы
extern FileSystem *TheFileSystem;
// Подсистема ресурсов и кэширования
extern ResourceCache *TheCache;
// Указатель на корневой элемент сцены
extern Scene *TheScene;
// Посистема времени
extern Time *TheTime;
// Сервер
extern Server *TheServer;
// Тип приложения - клиент или сервер
extern TypeApplication TheTypeApplication;
// Текстовый чат   
extern Chat *TheChat;


// Переменные для клиента
// Указатель на графическую подсистему
extern UI *gUI;
// Корневой элемент ГИП (Графический интерфейс пользователя - GUI)
extern UIElement *gUIRoot;
// Указатель на подсистему ввода
extern Input *gInput;
// Указатель на рендер
extern Renderer *gRenderer;
// Указатель на графическую подсистему
extern Graphics *gGraphics;
// Консоль
extern Console *gConsole;
// Отладочный интерфейс
extern DebugHud *gDebugHud;
// Звуковая подсистема
extern Audio *gAudio;
// Захват звука с микрофона
extern AudioCapturer *gAudioCapturer;
// Подсистема локализации
extern Localization *gLocale;
// Подсистема отладочного рендера
extern DebugRenderer *gDebugRenderer;
// Подсистема физической симуляции
extern PhysicsWorld *gPhysicsWorld;
// Видовая камера
extern CameraUni *gCamera;
// Сетевой клиент для связи по сети
extern Client *gClient;
// Игровой ГИП
extern GameGUI *gGameGUI;
// Окно, открывающееся в игре по нажатию клавиши Esc
extern WindowGameESC *gWindowGameESC;

extern String  gIPAddress;
extern unsigned short gNumPort;

extern Battler *gTankist;
extern Game *gGame;
extern WindowSettings *gWindowSettings;
extern Settings *gSet;
extern Counters *gCounters;
