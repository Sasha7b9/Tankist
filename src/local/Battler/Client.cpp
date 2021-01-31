#include "stdafx.h"


static String<> commandLine;

PI_ENTER_POINT(Client); //-V2567 //-V2511


Client::Client() :
    Application(),
    Singleton<Client>(TheGame),
    serverCommandObserver(this, &Client::HandleServerCommand),
    displayEventHandler(&HandleDisplayEvent),
    vehicleModelReg((ModelType::S)ModelType::Vehicle, "Simple Vehicle", "models/car", ModelRegistrationFlag::Precache, ControllerType::Vehicle),
    controllerReg(ControllerType::Vehicle, "Simple Vehicle"),
    locatorReg(kLocatorSpawn, "Spawn Location")
{
    gMaster.Connnect();

    PiLOG_ADDOUT(Logger::Out::Console | Logger::Out::File, "client.log");

    PiLOG_WRITE("Client log");

    TheHangarWindow = new HangarWindow(); //-V2511

    TheInterfaceMgr->AddWidget(TheHangarWindow);

    TheEngine->AddCommand(new Command("server", &serverCommandObserver)); //-V2511

    MainServer::Create();

    Variable *value = TheEngine->InitVariable("ipHangar", "127.0.0.1");

    auto selfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);

    TheMainServer->RequestConnect(value->GetValue().c_str(), ConnectorTCP::ParseAddress(selfAddress.c_str()).second);

    //TheConsoleWindow->Clear();
    //TheConsoleWindow->EnterForeground();

    TheDisplayMgr->InstallDisplayEventHandler(&displayEventHandler);

    prevEscapeProc = TheInputMgr->GetEscapeProc();

    prevEscapeCookie = TheInputMgr->GetEscapeCookie();

    TheInputMgr->SetEscapeProc(&EscapeProc, this);

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    vehicleController = nullptr;

    useAction = new UseAction; //-V2511
    TheInputMgr->AddAction(useAction);

    forwardAction = new MovementAction(ActionType::Forward, kMovementForward); //-V2511
    backwardAction = new MovementAction(ActionType::Backward, kMovementBackward); //-V2511
    leftAction = new MovementAction(ActionType::Left, kMovementLeft); //-V2511
    rightAction = new MovementAction(ActionType::Right, kMovementRight); //-V2511
    upAction = new MovementAction(ActionType::Up, kMovementUp); //-V2511
    downAction = new MovementAction(ActionType::Down, kMovementDown); //-V2511

    TheInputMgr->AddAction(backwardAction);
    TheInputMgr->AddAction(leftAction);
    TheInputMgr->AddAction(rightAction);
    TheInputMgr->AddAction(upAction);
    TheInputMgr->AddAction(downAction);
    TheInputMgr->AddAction(forwardAction);

    //TheMessageMgr->SetLatency(1500);

    //TheMessageMgr->SetLosses(50.0F);
}


void Client::AcceptActions()
{
    useAction = new UseAction; //-V2511
    TheInputMgr->AddAction(useAction);

    forwardAction = new MovementAction(ActionType::Forward, kMovementForward); //-V2511
    backwardAction = new MovementAction(ActionType::Backward, kMovementBackward); //-V2511
    leftAction = new MovementAction(ActionType::Left, kMovementLeft); //-V2511
    rightAction = new MovementAction(ActionType::Right, kMovementRight); //-V2511
    upAction = new MovementAction(ActionType::Up, kMovementUp); //-V2511
    downAction = new MovementAction(ActionType::Down, kMovementDown); //-V2511

    TheInputMgr->AddAction(backwardAction);
    TheInputMgr->AddAction(leftAction);
    TheInputMgr->AddAction(rightAction);
    TheInputMgr->AddAction(upAction);
    TheInputMgr->AddAction(downAction);
    TheInputMgr->AddAction(forwardAction);
}


Client::~Client()
{
    delete TheHangarWindow; //-V2511

    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);

    delete useAction; //-V2511

    delete forwardAction; //-V2511
    delete downAction; //-V2511
    delete upAction; //-V2511
    delete rightAction; //-V2511
    delete leftAction; //-V2511
    delete backwardAction; //-V2511

    MainServer::Destroy();

    TheInputMgr->SetEscapeProc(prevEscapeProc, prevEscapeCookie);
}


void Client::ApplicationTask()
{
    TheNetworkWidget->UpdateState();
}


void Client::HandleServerCommand(Command *, pchar text)
{
    String<> param(text);

    if (param == "kill")
    {
        ServerKillMessage message;
        TheMainServer->SendMessage(PlayerType::Server, message);
    }
}


World *Client::ConstructWorld(pchar name, void *)
{
    // Эта функция вызывается, когда загружается новый мир. Должно вернуть указатель на недавно созданный подкласс класса World.

    return (new GameWorld(name)); //-V2511
}


void Client::HandleDisplayEvent(const DisplayEventData *eventData, void *)
{
    // Эта функция вызывается, когда происходит событие отображения(потому что мы зарегистрировал его в конструкторе игр).
    if(eventData->eventType == EventDisplay::Change)
    {
        // Разрешение экрана изменилось. Обращайтесь соответственно.
    }
}


void Client::EscapeProc(void *)
{
    MenuWindow::Open();
}


EngineResult::B Client::LoadWorld(pchar name)
{
    return TheWorldMgr->LoadWorld(name);
}


void Client::CreatePlayer(const RespawnDoMessage *message)
{
    GameWorld *world = static_cast<GameWorld *>(TheWorldMgr->GetWorld());
    const LocatorMarker *locator = world->GetSpawnLocator();
    if (locator)
    {
        // Вычислите угол, соответствующий направлению, на которое персонаж изначально смотрит.

        const Vector3D direction = locator->GetWorldTransform()[0];
        float azimuth = Atan(direction.y, direction.x);

        // Загрузите модель автомобиля и подключите к ней контроллер.

        Model *model = Model::Get(ModelType::Vehicle);

        TheController = new VehicleController(azimuth, true); //-V2511
        TheController->SetControllerIndex(message->index); //-V522
        model->SetController(TheController);

        // Поместите модель в мир внутри зоны локатора.

        Zone *zone = locator->GetOwningZone();
        model->SetNodePosition(zone->GetInverseWorldTransform() * locator->GetWorldPosition());
        zone->AppendNewSubnode(model);

        if(message->key == TheMessageMgr->GetLocalPlayer()->GetPlayerKey())
        {
            // Установите текущую камеру в мире, чтобы быть нашей камерой преследования. Мир не будет отображаться без установленной камеры.

            ChaseCamera *camera = world->GetChaseCamera();
            camera->GetObject()->SetFocalLength(1.0F);
            world->SetCamera(camera);
            model->AppendSubnode(camera);

            float azm = Atan(direction.y, direction.x);
            float alt = 0.0F;

            float cosAlt = Cos(alt);
            float sinAlt = Sin(alt);

            float cosAzm = Cos(azm);
            float sinAzm = Sin(azm);

            Vector3D view(cosAzm * cosAlt, sinAzm * cosAlt, sinAlt);
            Vector3D right(sinAzm, -cosAzm, 0.0F);
            Vector3D down = view % right;

            Point3D position(0.0F, 0.0F, 0.5F);
            Point3D p1(position.x, position.y, position.z + 0.5F);
            Point3D p2 = p1 + view * 0.5F;

            // Установите положение камеры и ориентацию.

            camera->SetNodeTransform(right, down, view, p2);
        }

        players.Append(new GamePlayer(message->key, TheController)); //-V2511
    }
}


void Client::UnloadWorld(void)
{
    TheWorldMgr->UnloadWorld();

    TheMessageMgr->EndGame();

    TheGame->vehicleController = nullptr;
}
