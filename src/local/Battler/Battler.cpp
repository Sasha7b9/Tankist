/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "Objects/Vehicle.h"
#include "Battler.h"
#include "globals.h"
#include "CommonFunctions.h"
#include "Network/Chat.h"
#include "Graphics/ImageT.h"


#ifdef WIN32
#pragma warning(push, 0)
#endif
URHO3D_DEFINE_APPLICATION_MAIN(Battler)
#ifdef WIN32
#pragma warning(pop)
#endif



Battler::Battler(Context* context) :
    Application(context)
{
    Vehicle::RegisterObject(context);

    TheContext = context_;

    TheSet = new Settings();
}


void Battler::Setup()
{
    Vector<String> argumensts = GetArguments();

    if (!ParseArguments(argumensts, TheTypeApplication, TheIPAddress, TheNumPort))
    {
#ifdef WIN32
        URHO3D_LOGERROR("To rum application type tankist.exe -{client|server} [-ip:xxx.xxx.xxx.xxx] -port:xxx");
#else
        URHO3D_LOGERROR("To rum application type ./tankist -{client|server} [-ip:xxx.xxx.xxx.xxx] -port:xxx");
#endif
        exit = true;
    }

    TheLog = new Log(context_);
    TheLog->SetLevel(LOG_INFO);

    if (TheTypeApplication == Type_Client)
    {
        TheLog->Open("client.log");
    }
    else
    {
        TheLog->Open("server.log");
    }

    TheAudio = GetSubsystem<Audio>();

#ifdef WIN32
    TheAudioCapturer = new AudioCapturer();
    TheAudioCapturer->Start();
#endif

    TheNetwork = GetSubsystem<Network>();
    TheFileSystem = GetSubsystem<FileSystem>();
    TheCache = GetSubsystem<ResourceCache>();


    TheCache->AddResourceDir(TheFileSystem->GetProgramDir() + "TankistData");
    
    TheCache->AddResourceDir(TheFileSystem->GetProgramDir() + "../../../../../../out/debug/TankistData");
    //TheCache->AddResourceDir(TheFileSystem->GetProgramDir() + "distr\\TankistData");
    //TheCache->AddResourceDir(TheFileSystem->GetProgramDir() + "..\\..\\out\\distr\\TankistData");

    TheTime = GetSubsystem<Time>();

    if (TheTypeApplication == Type_Client)
    {
        TheUI = GetSubsystem<UI>();
        TheUIRoot = TheUI->GetRoot();
        TheInput = GetSubsystem<Input>();
    }

    engineParameters_["Headless"] = TheTypeApplication == Type_Server;
    engineParameters_["WindowTitle"] = "Battler WaT";
    engineParameters_["LogName"] = TheFileSystem->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";

    engineParameters_["FrameLimiter"] = false;
    engineParameters_["FullScreen"] = TheSet->Get(FULLSCREEN);
    engineParameters_["Sound"] = true;
    engineParameters_["WindowWidth"] = TheSet->Get(WINDOW_WIDTH);
    engineParameters_["WindowHeight"] = TheSet->Get(WINDOW_HEIGHT);
    //engineParameters_["WindowPositionY"] = 20;
    //engineParameters_["WindowPositionX"] = gTypeConnection == Connection_Server ? 20 : 700;

    // Construct a search path to find the resource prefix with two entries:
    // The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary
    // when it is still in build tree
    // The second and third entries are possible relative paths from the installed program/bin directory to the asset
    // directory -- these entries are for binary when it is in the Urho3D SDK installation location
    if (!engineParameters_.Contains("ResourcePrefixPaths"))
    {
        engineParameters_["ResourcePrefixPaths"] =
            //            "d:\\My\\TankistU3D\\out\\debug\\;d:\\My\\TankistU3D\\out\\debug\\TankistData";
            "c:/My/prog/TankistU3D/out/debug";
    }
}


void Battler::Start()
{
    if (TheTypeApplication == Type_Client)
    {
        TheLocale = GetSubsystem<Localization>();
        TheLocale->LoadJSONFile("Strings.json");
        TheLocale->SetLanguage(TheSet->Get(LANGUAGE) == 0 ? "ru" : "en");
        TheLocale->SetLanguage(TheSet->Get(LANGUAGE) == 0 ? "en" : "ru");

        TheGraphics = GetSubsystem<Graphics>();
        TheRenderer = GetSubsystem<Renderer>();

        if(TheSet->FirstStart())
        {
            /*
            IntVector2 res = TheGraphics->GetDesktopResolution();
            TheSet->Set(WINDOW_WIDTH, res.x_);
            TheSet->Set(WINDOW_HEIGHT, res.y_);
            TheGraphics->SetMode(TheSet->Get(WINDOW_WIDTH), TheSet->Get(WINDOW_HEIGHT));
            */
        }

        SetWindowTitleAndIcon();

        CreateConsoleAndDebugHud();

        CreateUI();
    }

    CreateScene();

    SubscribeToEvents();

    TheTankist = this;

    TheCounters = new Counters();

    if (TheTypeApplication == Type_Server)
    {
        TheServer = new Server(context_);
        TheServer->Start(TheNumPort);

        CreateListFiles();

        TheChatLog = new ChatLog(context_);

        TheChat = new Chat(TheContext, Chat::Chat_Server);
        TheChat->Listen(PORT_CHAT);

    }
    
    if (TheTypeApplication == Type_Client)
    {
        TheCamera = new CameraUni(context_);
        TheCamera->SetupViewport();

        TheClient = new Client(context_);
        TheClient->ConnectToServer();

        CreateInstructions();

        TheChat = new Chat(TheContext, Chat::Chat_Client);
        TheChat->Connect(TheIPAddress.CString(), PORT_CHAT);
    }

    TheGame = new Game(TheContext);
    TheGame->Start();
}


void Battler::Stop()
{
    if (TheClient)
    {
        TheClient->Disconnect();
        TheSet->Save();
    }

#ifdef WIN32
    TheAudioCapturer->Stop();
#endif

    //engine_->DumpResources(true);
    //engine_->DumpProfiler();
    //engine_->DumpMemory();
    LOG_WRITE("out");
    TheLog->Close();

    SAFE_DELETE(TheCounters);
    SAFE_DELETE(TheGame);
    SAFE_DELETE(TheCamera);
    SAFE_DELETE(TheLog);
    SAFE_DELETE(TheClient);
    SAFE_DELETE(TheServer);
    SAFE_DELETE(TheScene);
    SAFE_DELETE(TheChat);
    SAFE_DELETE(TheChatLog);
}


void Battler::CreateScene()
{
    TheScene = new Scene(context_);

    TheScene->CreateComponent<Octree>(LOCAL);
    ThePhysicsWorld = TheScene->CreateComponent<PhysicsWorld>(LOCAL);

    if(TheTypeApplication == Type_Client)
    {
        TheDebugRenderer = TheScene->CreateComponent<DebugRenderer>(LOCAL);
    }

    Node* zoneNode = TheScene->CreateChild("Zone", LOCAL);
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(4000.0f);
    zone->SetFogEnd(5000.0f);
    zone->SetBoundingBox(BoundingBox(-2000.0f, 2000.0f));

    // Create a directional light with cascaded shadow mapping
    Node* lightNode = TheScene->CreateChild("DirectionalLight", LOCAL);
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);

    // Create heightmap terrain with collision
    Node* terrainNode = TheScene->CreateChild("Terrain");
    terrainNode->SetPosition(Vector3::ZERO);
    Terrain* terrain = terrainNode->CreateComponent<Terrain>();
    terrain->SetViewMask(VIEW_MASK_TERRAIN);
    terrain->SetPatchSize(64);
    terrain->SetSpacing(Vector3(2.0f, 1.0f, 2.0f)); // Spacing between vertices and vertical resolution of the height map
    terrain->SetSmoothing(true);
    terrain->SetHeightMap(TheCache->GetResource<Image>("Landscape/land1.png"));
    terrain->SetMaterial(TheCache->GetResource<Material>("Landscape/Terrain.xml"));
    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain->SetOccluder(true);

    RigidBody* body = terrainNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1); // Use layer bitmask 2 for static geometry
    body->SetFriction(1.0f);
    CollisionShape* shape = terrainNode->CreateComponent<CollisionShape>();
    shape->SetTerrain();

    //TheScene->GetComponent<PhysicsWorld>()->SetFps(300);
}


void Battler::SubscribeToEvents()
{
    if (TheTypeApplication == Type_Client)
    {
        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Battler, HandleKeyDown));
        SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(Battler, HandleKeyUp));
        SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Battler, HandleLanguageChanged));
        SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Battler, HandlePostRenderUpdate));
    }

    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Battler, HandlePostUpdate));
}


void Battler::CreateUI()
{
#ifdef WIN32
    XMLFile* uiStyle = TheCache->GetResource<XMLFile>("UI/TankistStyle.xml");
    // Set style to the UI root so that elements will inherit it
    TheUIRoot->SetDefaultStyle(uiStyle);

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it can interact with the login UI
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(uiStyle);
    TheUI->SetCursor(cursor);
    // Set starting position of the cursor at the rendering window center
    cursor->SetPosition(TheGraphics->GetWidth() / 2, TheGraphics->GetHeight() / 2);

    SharedPtr<UIElement> container(TheUIRoot->CreateChild<UIElement>());
    container->SetFixedSize(200, 300);
    container->SetPosition(0, 100);
    container->SetLayoutMode(LM_VERTICAL);
    container->SetStyleAuto();

    statisticsWindow = TheUIRoot->CreateChild<Text>();
    statisticsWindow->SetStyleAuto();
    statisticsWindow->SetPosition(TheUIRoot->GetWidth() - 200, 0);
    statisticsWindow->SetColor(Color::BLACK);

    TheWindowGameESC = new WindowGameESC(context_);

    TheWindowSettings = new WindowSettings(context_);

    TheGameGUI = new GameGUI(context_);
#endif
}


void Battler::UpdateCamera()
{
    if (TheTypeApplication != Type_Server)
    TheUI->GetCursor()->SetVisible(!TheInput->GetMouseButtonDown(MOUSEB_RIGHT));

    TheCamera->MoveFromMouse();

    if (TheTypeApplication == Type_Client)
    {
        static bool cameraIsAttached = false;

        if (!cameraIsAttached)
        {
            cameraIsAttached = TheClient->AttachCameraToNode();
        }
    }
}


void Battler::SetWindowTitleAndIcon()
{
    Image* icon = TheCache->GetResource<Image>("Textures/UrhoIcon.png");
    TheGraphics->SetWindowIcon(icon);
    //TheGraphics->SetWindowTitle("Battler WaT");
}


void Battler::CreateConsoleAndDebugHud()
{
    XMLFile* xmlFile = TheCache->GetResource<XMLFile>("UI/TankistStyle.xml");

    Console* console = engine_->CreateConsole();
    TheConsole = GetSubsystem<Console>();
    console->SetDefaultStyle(xmlFile);
    console->GetBackground()->SetOpacity(0.8f);

    TheDebugHud = engine_->CreateDebugHud();
    TheDebugHud->SetDefaultStyle(xmlFile);
}


bool Battler::ParseArguments(Vector<String> &arguments, TypeApplication &type, String &address, unsigned short &port)
{
    if (arguments.Size() == 2 && arguments[0] == "-server")
    {
        if (arguments[1].Length() > 6 && GetNumPort(arguments[1], port))     // "-port:"
        {
            type = Type_Server;
            return true;
        }
    }

    if (arguments.Size() == 3 && arguments[0] == "-client")
    {
        String &arg1 = arguments[1];
        String &arg2 = arguments[2];

        if (arg1.Length() > 9)   // "-address:"
        {
            address = arg1.Substring(4);

            if (GetNumPort(arg2, port))
            {
                type = Type_Client;
                return true;
            }
        }
    }

    return false;
}


bool Battler::GetNumPort(String &str, unsigned short &port)
{
    String strPort = str.Substring(6);

    long int numPort = strtol(strPort.CString(), nullptr, 10);

    if (numPort == 0L)
    {
        return false;
    }

    port = (unsigned short)numPort;

    return true;
}


void Battler::CreateInstructions()
{
    Text *instructionText = TheUIRoot->CreateChild<Text>();
    instructionText->SetText("Press F12 to help");
    instructionText->SetFont(TheCache->GetResource<Font>("Fonts/CRL.ttf"), 10);

    instructionText->SetHorizontalAlignment(HA_LEFT);
    instructionText->SetVerticalAlignment(VA_TOP);
    instructionText->SetPosition(0, 0);

    instructionText = TheUIRoot->CreateChild<Text>(INSTRUCTION);

    instructionText->SetFont(TheCache->GetResource<Font>("Fonts/CRL.ttf"), 15);
    instructionText->SetTextAlignment(HA_CENTER);
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, TheUI->GetRoot()->GetHeight() / 4);
    instructionText->SetVisible(false);
}


void Battler::UpdateStatisticWindow()
{
    statisticsWindow->SetText(ToString("%d users online\n\n", numClients) +
                              String("speed in = ") + String((int)(bytesInPerSec / 1024.0f + 0.5f)) + String(" kB/s\n") +
                              String("speed out = ") + String((int)(bytesOutPerSec / 1024.0f + 0.5f)) + String(" kB/s\n") +
                              String("ping = ") + String((int)(ping * 1000.0f)) + String(" ms\n\n") +
                              String("load server CPU = ") + String(loadCPU * 100.0f) + " %\n" +
                              String("server in = ") + String((int)(bytesInPerSecServer / 1024.0f + 0.5f)) + String(" kB/s\n") +
                              String("server out = ") + String((int)(bytesOutPerSecServer / 1024.0f + 0.5f)) + String(" kB/s\n")
                              );
}


void Battler::SetPing(float pingMS)
{
    this->ping = pingMS;
    UpdateStatisticWindow();
}


void Battler::SetLoadCPU(float loadCPU_)
{
    loadCPU = loadCPU_;
    UpdateStatisticWindow();
}


void Battler::SetNumClients(int numClients_)
{
    numClients = numClients_;
    UpdateStatisticWindow();
}


void Battler::SetBytesInPerSec(float bytesInPerSec_)
{
    bytesInPerSec = bytesInPerSec_;
    UpdateStatisticWindow();
}


void Battler::SetBytesOutPerSec(float bytesOutPerSec_)
{
    bytesOutPerSec = bytesOutPerSec_;
    UpdateStatisticWindow();
}


void Battler::SetBytesInPerSecServer(float bytes)
{
    bytesInPerSecServer = bytes;
    UpdateStatisticWindow();
}


void Battler::SetBytesOutPerSecServer(float bytes)
{
    bytesOutPerSecServer = bytes;
    UpdateStatisticWindow();
}


void Battler::Exit()
{
    engine_->Exit();
}
