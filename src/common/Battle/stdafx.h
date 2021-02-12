/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#ifdef SendMessage
#undef SendMessage
#endif
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/Protocol.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UI.h>
#ifdef WIN32
#pragma warning(pop)
#endif


using namespace Urho3D;


#include "glob_engine.h"
#include "defines.h"

#include "Battle.h"
#include "Network/SServer.h"
#include "Network/Game/_TConnection.h"
#include "Scene/Objects/_ObjectState.h"
#include "Network/Game/_GameMessages.h"
#include "Scene/_GameScene.h"
#include "Scene/Cameras/_MainCamera.h"
#include "Scene/Objects/_Vehicle.h"
#include "Utils/_LogU.h"

#include "glob_game.h"
