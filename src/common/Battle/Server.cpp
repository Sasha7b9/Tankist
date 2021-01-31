#include "stdafx.h"


static String<> commandLine;

PI_ENTER_POINT(Server); //-V2567 //-V2511


Server::Server() :
    Application(),
    Singleton<Server>(TheGame),
    vehicleModelReg((ModelType::S)ModelType::Vehicle, "Simple Vehicle", "models/car", ModelRegistrationFlag::Precache, ControllerType::Vehicle),
    controllerReg(ControllerType::Vehicle, "Simple Vehicle"),
    locatorReg(kLocatorSpawn, "Spawn Location")
{
    PiLOG_ADDOUT(Logger::Out::Console | Logger::Out::File, "server.log");
    PiLOG_WRITE("Server log");

    gMaster.Connnect();

    auto selfAddress = gMaster.GetValue(MASTER_GET_ADDRESS_HANGAR);
    uint16 port = ConnectorTCP::ParseAddress(selfAddress.c_str()).second;

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    TheGame->LoadWorld("worlds/world1");

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(port);
    TheNetworkMgr->SetBroadcastPortNumber(port);
    TheMessageMgr->SetMaxPlayerCount(30);
    TheMessageMgr->BeginMultiplayerGame(true);
}


Server::~Server()
{
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);

}


void Server::ApplicationTask()
{
    static uint prevTime = 0;

    static uint speedIn = 0;
    static uint speedOut = 0;

    CalculateTraffic(&speedIn, &speedOut);

    if (TheTimeMgr->GetAbsoluteTime() > prevTime + 500)
    {
        prevTime = TheTimeMgr->GetAbsoluteTime();

        TheMessageMgr->SendMessage(PlayerType::Clients, ServerInfoMessage(&speedIn, &speedOut));
    }
}


World *Server::ConstructWorld(pchar name, void *)
{
    // Эта функция вызывается, когда загружается новый мир. Должно вернуть указатель на недавно созданный подкласс класса World.

    return (new GameWorld(name)); //-V2511
}


EngineResult::B Server::LoadWorld(pchar name)
{
    return TheWorldMgr->LoadWorld(name);
}


void Server::CreateNewPlayer(const RespawnDoMessage *message)
{
    PiLOG_ENTER;

    GameWorld *world = static_cast<GameWorld *>(TheWorldMgr->GetWorld());

    const LocatorMarker *locator = world->GetSpawnLocator();
    if (locator)
    {
        // Вычислите угол, соответствующий направлению, на которое персонаж изначально смотрит.

        const Vector3D direction = locator->GetWorldTransform()[0];
        float azimuth = Atan(direction.y, direction.x);

        // Загрузите модель автомобиля и подключите к ней контроллер.

        Model *model = Model::Get(ModelType::Vehicle);
        VehicleController *controller = new VehicleController(azimuth, true); //-V2511
        controller->SetControllerIndex(message->index); //-V522
        model->SetController(controller);

        // Поместите модель в мир внутри зоны локатора.

        Zone *zone = locator->GetOwningZone();
        model->SetNodePosition(zone->GetInverseWorldTransform() * locator->GetWorldPosition());
        zone->AppendNewSubnode(model);

        players.Append(new GamePlayer(message->key, controller)); //-V2511
    }
}


void Server::UnloadWorld(void)
{
    TheWorldMgr->UnloadWorld();

    TheMessageMgr->EndGame();
}


void Server::CalculateTraffic(uint *speedIn, uint *speedOut)
{
    static uint prevSend = 0;   // Передано байт в текущую секунду
    static uint prevRecv = 0;   // Принято байт в текущую секунду
    static uint time = 0;       // Время начала текущей секунды

    if (TheTimeMgr->GetAbsoluteTime() >= time + 1000)
    {
        *speedIn = TheNetworkMgr->GetBytesRecv() - prevRecv;
        *speedOut = TheNetworkMgr->GetBytesSend() - prevSend;

        prevRecv = TheNetworkMgr->GetBytesRecv();
        prevSend = TheNetworkMgr->GetBytesSend();

        time = TheTimeMgr->GetAbsoluteTime();
    }
}
