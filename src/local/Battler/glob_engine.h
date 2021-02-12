/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


/*
*   Глобальыне указатели на подсистемы движка
*/


extern Context          *TheContext;        // Глобальный контекст
extern FileSystem       *TheFileSystem;     // Подсистема для работы с файловой системы
extern Log              *TheLog;            // Подсистема логгирования
extern Network          *TheNetwork;        // Сетевая система
extern ResourceCache    *TheCache;          // Подсистема ресурсов и кэширования
extern Time             *TheTime;           // Посистема времени

extern Audio            *TheAudio;          // Звуковая подсистема
extern Console          *TheConsole;        // Консоль
extern DebugHud         *TheDebugHud;       // Отладочный интерфейс
extern DebugRenderer    *TheDebugRenderer;  // Подсистема отладочного рендера
extern Graphics         *TheGraphics;       // Указатель на графическую подсистему
extern Localization     *TheLocale;         // Подсистема локализации
extern PhysicsWorld     *ThePhysicsWorld;   // Подсистема физической симуляции
extern Renderer         *TheRenderer;       // Указатель на рендер
extern UI               *TheUI;             // Указатель на графическую подсистему
extern UIElement        *TheUIRoot;         // Корневой элемент ГИП (Графический интерфейс пользователя - GUI)

extern String           TheIPAddress;
extern unsigned short   TheNumPort;
