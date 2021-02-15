// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <Bullet/src/BulletDynamics/ConstraintSolver/btSliderConstraint.h>

#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/UI/CheckBox.h>

#include <Urho3D/Audio/Audio.h>

#include <Urho3D/Container/Ptr.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/Core/Thread.h>
#include <Urho3D/Core/Variant.h>


#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/EngineDefs.h>

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/StaticModelGroup.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/DebugRenderer.h>

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Input/Input.h>

#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>

#include <Urho3D/Math/Ray.h>

#ifdef SendMessage
#undef SendMessage
#endif

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/Protocol.h>

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RaycastVehicle.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/PhysicsEvents.h>

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Resource/ResourceEvents.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Scene/LogicComponent.h>

#include <Urho3D/DebugNew.h>

#include <Urho3D/UI/UI.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>


#include <thread>

#pragma comment(lib, "ws2_32.lib")
#include <d3d9types.h>

#ifdef WIN32
#pragma warning(pop)
#endif

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#define SOCKET int
//#define closesocket close
//#define WSAGetLastError() errno

#include "defines.h"

using namespace Urho3D;

#include "Battler.h"
#include "GUI/Instructions.h"
#include "GUI/Logo.h"
#include "Input/IInput.h"
#include "Network/Game/_TConnection.h"
#include "Scene/Objects/_ObjectState.h"
#include "Network/Game/_GameMessages.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Network/CServer.h"
#include "Scene/_GameScene.h"
#include "Scene/Objects/_Vehicle.h"
#include "Scene/Cameras/_MainCamera.h"
#include "Utils/_LogU.h"

#include "glob_engine.h"
#include "glob_game.h"
