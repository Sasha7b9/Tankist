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
extern UI *TheUI;
// Корневой элемент ГИП (Графический интерфейс пользователя - GUI)
extern UIElement *TheUIRoot;
// Указатель на подсистему ввода
extern Input *TheInput;
// Указатель на рендер
extern Renderer *TheRenderer;
// Указатель на графическую подсистему
extern Graphics *TheGraphics;
// Консоль
extern Console *TheConsole;
// Отладочный интерфейс
extern DebugHud *TheDebugHud;
// Звуковая подсистема
extern Audio *TheAudio;
// Захват звука с микрофона
//extern AudioCapturer *TheAudioCapturer;
// Подсистема локализации
extern Localization *TheLocale;
// Подсистема отладочного рендера
extern DebugRenderer *TheDebugRenderer;
// Подсистема физической симуляции
extern PhysicsWorld *ThePhysicsWorld;
// Видовая камера
//extern CameraUni *TheCamera;
// Сетевой клиент для связи по сети
extern Client *TheClient;
// Игровой ГИП
extern GameGUI *TheGameGUI;
// Окно, открывающееся в игре по нажатию клавиши Esc
extern WindowGameESC *TheWindowGameESC;

extern String  TheIPAddress;
extern unsigned short TheNumPort;

extern Battler *TheTankist;
extern Game *TheGame;
extern WindowSettings *TheWindowSettings;
extern Settings *TheSet;
extern Counters *TheCounters;
