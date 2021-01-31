#include "stdafx.h"
#include "globals.h"
#include "Tankist.h"
#include "GUI/HangarGUI.h"
#include "GameWorld.h"
#include "Input.h"
#include "Network/Messages.h"
#include "GUI/GameGUI.h"
#include "Objects/ChaseCamera.h"
#include "Objects/Vehicle.h"


PI_ENTER_POINT(Tankist);

/// Переменные клиента
/// Адрес сервера
static NetworkAddress addressServer;

/// Переменные сервера

struct PlayerInfo
{
    static uint id;
    String<>    nameNode;
    Player*     player;
//    Tank*       tank;
    void CreateName()
    {
        nameNode = String<>("node") + String<>(id++);
    }
};

uint PlayerInfo::id = 0;

/// Список игроков на сервере
Array<PlayerInfo*> players;



Tankist::Tankist()
    : Singleton<Tankist>(TheGame),
    locatorReg(kLocatorSpectator, "Spectator Camera"),
    vehicleModelReg(ModelType::Vehicle, "Vehicle", "19/model/car", Pi::ModelRegistrationFlag::Precache, ControllerType::Vehicle),
    controllerReg(ControllerType::Vehicle, "Vehicle"),
    serverCommandObserver(this, &Tankist::HandleServerCommand),
    commandServer("server", &serverCommandObserver)
//    tankControllerReg(kControllerTank, "Tank Controller")
{
    TheWorldMgr->SetWorldCreator(&CreateWorld);

    if (PiHEADLESS)
    {
        TheWorldMgr->LoadWorld("worlds/world1");
//        Tank::Construct();
    }
    else
    {
        static const Command::Parameters paramsCommand = { "work with server" };
        commandServer.SetParameters(&paramsCommand);
        TheEngine->AddCommand(&commandServer);

        Input::Construct();

        gui = new HangarGUI();
        if (gui)
        {
            gui->Hide();

            TheInterfaceMgr->AddWidget(gui);
        }

        TheInterfaceMgr->SetInputManagementMode(Pi::InputManagementMode::Automatic);
    }

    LoadWorld("worlds/world1");
}


Tankist::~Tankist()
{
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);
}


World *Tankist::CreateWorld(const char *name, void *)
{
    return (new GameWorld(name));
}


void Tankist::HandleGameEvent(GameEvent, const void *)
{
}


void Tankist::ReceiveMessage(Player * /*sender*/, const NetworkAddress & /*address*/, const Message * /*message*/)
{
    return;
}


Message *Tankist::CreateMessage(Pi::MessageType::E type, Decompressor& /*data*/) const
{
    if (type == MessageType::Movement)
    {
        return new MessageMovement();
    }
    else if (type == MessageType::Replicate)
    {
        return new  MessageReplicate();
    }
    else if (type == MessageType::TankInfo)
    {
        return new MessageTankInfo();
    }
    else
    {
        // здесь ничего
    }

    return nullptr;
}


void Tankist::HandleConnectionEvent(ConnectionEvent::E event, const NetworkAddress &address, const void * /*param*/)
{
    if (PiHEADLESS)
    {

    }
    else
    {
        if (event == ConnectionEvent::ServerAccepted)
        {
            GameGUI::AddSystemMessage("Connected to server");
            addressServer = address;
        }
        else if (event == ConnectionEvent::AttemptFailed)
        {
            GameGUI::AddSystemMessage("Can not connect to server");
            addressServer = address;
        }
        else
        {
            // здесь ничего
        }

        if (event == ConnectionEvent::ServerClosed)
        {
            GameGUI::AddSystemMessage("!!! Server losg !!!");
        }
    }
}


void Tankist::ApplicationTask()
{
    if (PiHEADLESS)
    {

    }
    else
    {
        GameGUI::SetPing(TheNetworkMgr->GetPing(addressServer));

        if (!TheWorldMgr->GetWorld())
        {
            WidgetEventData data;
            data.eventType = Pi::EventWidget::Activate;

            gui->HandleButtonGo(nullptr, &data);

//            Tank::Construct();

//            if (PiSINGLE)
//            {
//                /*
//                TheTank = Tank::Create();
//                TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(TheTank->GetModel());
//                TheTank->GetController()->GetTargetNode()->SetNodePosition({ 0.0F, 0.0F, 10.0F });
//                */
//                //TheTank->GetController()->GetTargetNode()->SetNodeName(nameNode.c_str());
//            }
        }
    }
}


void Tankist::SendInformationAboutPlayersToNewPlayer(Player *)
{
//    for (PlayerInfo *info : players)
//    {
//        MessageTankInfo message(info->tank->GetController()->GetTargetNode()->GetNodePosition(), info->nameNode, true);
//        player->SendMessage(message);
//    }
}


void Tankist::HandlePlayerEvent(PlayerEvent::E event, Player *player, const void *)
{
    if (PiHEADLESS)
    {
        if (event == PlayerEvent::Connected)
        {
            SendInformationAboutPlayersToNewPlayer(player);

//            Tank *tank = Tank::Create();
//            TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(tank->GetModel());
//            tank->GetController()->GetTargetNode()->SetNodePosition(position);

            PlayerInfo *info = new PlayerInfo();
            if (info)
            {
                info->player = player;
                info->CreateName();
                //            info->tank = tank;

                players.AddElement(info);

                Point3D position = { Pi::Math::RandomFloat(-20.0F, 20.0F), Pi::Math::RandomFloat(-20.0F, 20.0F), 0.0F };

                MessageReplicate message(position, info->nameNode);

                player->SendMessage(message);
            }
        }
    }
    else
    {
        if (event == PlayerEvent::Connected)
        {
            GameGUI::AddSystemMessage("Join to game");

        }
        if (event == PlayerEvent::Disconnected)
        {
            GameGUI::AddSystemMessage("!!! Server lost !!!");
        }
    }
}


Pi::EngineResult::B Tankist::LoadWorld(const char *name)
{
    Pi::WorldResult::B result = TheWorldMgr->LoadWorld(name);
    if (result == Pi::WorldResult::Okay)
    {
        GameWorld *world = static_cast<GameWorld *>(TheWorldMgr->GetWorld());
        const LocatorMarker *locator = world->GetSpawnLocator();
        if (locator)
        {
            /// Если в мире был найден локатор спавна, поместите там автомобиль Гадюки.

            /// Функция BeginSinglePlayerGame () переводит Менеджер сообщений в режим одиночной игры.

            TheMessageMgr->BeginSinglePlayerGame();

            /// Вычислите угол, соответствующий направлению, на которое персонаж изначально смотрит.

            const Vector3D direction = locator->GetWorldTransform()[0];
            float azimuth = Atan(direction.y, direction.x);

            /// Загрузите модель автомобиля и подключите к ней контроллер.

            Model *model = Model::Get(ModelType::Vehicle);
            VehicleController *controller = new VehicleController(azimuth, true);
            model->SetController(controller);

            /// Поместите модель в мир внутри зоны локатора.

            Zone *zone = locator->GetOwningZone();
            model->SetNodePosition(zone->GetInverseWorldTransform() * locator->GetWorldPosition());
            zone->AppendNewSubnode(model);

            /// Установите текущую камеру в мире, чтобы быть нашей камерой преследования. Мир не будет отображаться без установленной камеры.

            ChaseCamera *camera = world->GetChaseCamera();
            camera->GetObject()->SetFocalLength(1.5f);
            camera->SetTargetModel(model);
            world->SetCamera(camera);

        }
    }

    return result;
}
