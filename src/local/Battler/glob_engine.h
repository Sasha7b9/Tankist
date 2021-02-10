#pragma once
#include <Urho3D/UI/UI.h>

/*
*   ���������� ��������� �� ���������� ������
*/


extern Context          *TheContext;        // ���������� ��������
extern FileSystem       *TheFileSystem;     // ���������� ��� ������ � �������� �������
extern Log              *TheLog;            // ���������� ������������
extern Network          *TheNetwork;        // ������� �������
extern ResourceCache    *TheCache;          // ���������� �������� � �����������
extern Scene            *TheScene;          // ��������� �� �������� ������� �����
extern Time             *TheTime;           // ��������� �������

extern Audio            *TheAudio;          // �������� ����������
extern Console          *TheConsole;        // �������
extern DebugHud         *TheDebugHud;       // ���������� ���������
extern DebugRenderer    *TheDebugRenderer;  // ���������� ����������� �������
extern Graphics         *TheGraphics;       // ��������� �� ����������� ����������
extern Input            *TheInput;          // ��������� �� ���������� �����
extern Localization     *TheLocale;         // ���������� �����������
extern PhysicsWorld     *ThePhysicsWorld;   // ���������� ���������� ���������
extern Renderer         *TheRenderer;       // ��������� �� ������
extern UI               *TheUI;             // ��������� �� ����������� ����������
extern UIElement        *TheUIRoot;         // �������� ������� ��� (����������� ��������� ������������ - GUI)

extern String           TheIPAddress;
extern unsigned short   TheNumPort;
