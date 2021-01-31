#pragma once

#pragma warning(push)

#pragma warning(disable:4514)   // 'xxx': unreferenced inline function has been removed
#pragma warning(disable:5026)   // 'xxx': move constructor was implicitly defined as deleted
#pragma warning(disable:5027)   // 'xxx': move assignment operator was implicitly defined as deleted

#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdarg>
#include <cstdio>

#include <Base/PiMemory.h>
#include <Graphics/PiRender.h>
#include <System/PiAudioCapture.h>
#include <Physics/PiCharacter.h>
#include <System/PiInput.h>
#include <Graphics/PiGraphics.h>
#include <System/PiApplication.h>
#include <Geometry/PiMesh.h>
#include <Geometry/PiGizmo.h>
#include <Interface/PiConfiguration.h>
#include <Interface/PiToolWindows.h>
#include <Geometry/PiPrimitives.h>
#include <Controllers/PiController.h>
#include <Effects/PiParticles.h>
#include <Network/Messages.h>
#include <World/PiCameras.h>
#include <World/PiModels.h>
#include <World/PiSources.h>
#include <World/PiWorld.h>
#include <Math/PiRandom.h>
#include <Interface/PiPaint.h>
#include <Physics/PiContacts.h>
#include <Physics/PiPhysics.h>
#include <World/PiWorld.h>
#include <Resource/PiPacking.h>
#include <System/PiTypes.h>
#include <System/PiSound.h>
#include <Interface/PiMutators.h>
#include <Interface/PiViewports.h>
#include <Physics/PiSimulation.h>
#include <Interface/PiWidgets.h>
#include <System/PiMain.h>
#include <Network/PiMessages.h>
#include <Utilities/PiString.h>
#include <World/PiCameras.h>

#pragma warning(pop)

#define SIZE_CHUNK_HEADER 4

using Pi::Action;
using Pi::Antivector3D;
using Pi::Application;
using Pi::Atan;
using Pi::Array;
using Pi::AutoRelease;

using Pi::BlendAnimator;
using Pi::BooleanSetting;
using Pi::BorderWidget;
using Pi::BoundingSphere;
using Pi::BoxGeometry;
using Pi::Box3D;

using Pi::Camera;
using Pi::CameraObject;
using Pi::CameraWidget;
using Pi::Ceil;
using Pi::CharacterController;
using Pi::ChunkHeader;
using Pi::Clamp;
using Pi::CollisionContact;
using Pi::CollisionData;
using Pi::ColorRGB;
using Pi::ColorRGBA;
using Pi::Command;
using Pi::CommandObserver;
using Pi::Compressor;
using Pi::ConnectionEvent;
using Pi::ConnectorKey;
using Pi::ConstVector2D;
using Pi::Contact;
using Pi::Controller;
using Pi::ControllerReg;
using Pi::Cos;
using Pi::CosSin;
using Pi::Cross;

using Pi::DiffuseAttribute;
using Pi::DiffuseTextureAttribute;
using Pi::DisplayEventData;
using Pi::DisplayEventHandler;
using Pi::Dot;
using Pi::Decompressor;

using Pi::Effect;
using Pi::EmissionAttribute;
using Pi::Exchange;
using Pi::ExclusiveObserver;

using Pi::Fabs;
using Pi::File;
using Pi::Fmax;
using Pi::FmaxZero;
using Pi::Fmin;
using Pi::FminZero;
using Pi::FrameAnimator;
using Pi::FrameAnimatorObserver;
using Pi::FrustumCamera;
using Pi::FrustumCameraObject;
using Pi::FrustumViewportWidget;

using Pi::GameEvent;
using Pi::GenericGeometry;
using Pi::Geometry;
using Pi::GeometryContact;
using Pi::GeometryObject;
using Pi::GeometryPolygon;
using Pi::GeometrySurface;
using Pi::GeometryVertex;
using Pi::Gizmo;

using Pi::Identity4D;
using Pi::ImageWidget;
using Pi::InfiniteLight;
using Pi::InfiniteLightObject;
using Pi::Integer2D;
using Pi::Integer3D;
using Pi::Interpolator;
using Pi::InputMgr;

using Pi::KeyboardEventData;
using Pi::KeyboardEventHandler;

using Pi::HashTable;
using Pi::HashTableElement;

using Pi::LineParticleSystem;
using Pi::Link;
using Pi::LinkTarget;
using Pi::List;
using Pi::ListElement;
using Pi::LocatorMarker;
using Pi::LocatorRegistration;

using Pi::Marker;
using Pi::MarkerType::S;
using Pi::MaterialObject;
using Pi::MaxZero;
using Pi::Message;
using Pi::Method;
using Pi::MethodReg;
using Pi::Model;
using Pi::ModelRegistration;
using Pi::MouseEventData;
using Pi::MouseEventHandler;
using Pi::Magnitude;
using Pi::Map;
using Pi::MapElement;
using Pi::Math::GetTrigTable;
using Pi::Math::Random;
using Pi::Math::RandomFloat;
using Pi::Math::RandomUnitVector3D;
using Pi::Matrix3D;
using Pi::Message;
using Pi::Min;
using Pi::Mutator;
using Pi::MutatorReg;
using Pi::Mutex;

using Pi::NetworkAddress;
using Pi::Node;

using Pi::Object;
using Pi::Observable;
using Pi::Observer;
using Pi::OmniSource;

using Pi::Packable;
using Pi::Packer;
using Pi::PackHandle;
using Pi::Painter;
using Pi::PanelMouseEventData;
using Pi::Player;
using Pi::PlayerEvent;
using Pi::Widget;
using Pi::PanelController;
using Pi::PanelEffect;
using Pi::Particle;
using Pi::ParticlePool;
using Pi::ParticleSystemReg;
using Pi::PlateGeometry;
using Pi::Point2D;
using Pi::Point3D;
using Pi::PointLight;
using Pi::PointLightObject;
using Pi::PrimitiveGeometry;
using Pi::PrimitiveGeometryObject;
using Pi::Property;
using Pi::PropertyReg;
using Pi::PushButtonWidget;

using Pi::RagdollController;
using Pi::Range;
using Pi::Ray;
using Pi::ReflectionAttribute;
using Pi::Renderable;
using Pi::Rect;
using Pi::RigidBodyContact;
using Pi::RigidBodyController;
using Pi::RigidBodyStatus;
using Pi::RootWidget;

using Pi::ScriptState;
using Pi::Shared;
using Pi::Setting;
using Pi::Singleton;
using Pi::Sin;
using Pi::Sound;
using Pi::SpectatorCamera;
using Pi::SpecularAttribute;
using Pi::SpecularTextureAttribute;
using Pi::SphereGeometry;
using Pi::SphereGeometryObject;
using Pi::Sqrt;
using Pi::Storage;
using Pi::String;

using Pi::TheAudioCaptureMgr;
using Pi::TerminatorChunk;
using Pi::Text::StringToInteger;
using Pi::TextWidget;
using Pi::Texture;
using Pi::TextureAttribute;
using Pi::TheConsoleWindow;
using Pi::TheDisplayMgr;
using Pi::TheEngine;
using Pi::TheGraphicsMgr;
using Pi::TheInputMgr;
using Pi::TheInterfaceMgr;
using Pi::TheMessageMgr;
using Pi::TheTimeMgr;
using Pi::TheWorldMgr;
using Pi::Thread;
using Pi::Transform4D;

using Pi::Unpacker;

using Pi::Variable;
using Pi::VariableObserver;
using Pi::Vector2D;
using Pi::Vector3D;
using Pi::Vector4D;
using Pi::VertexBuffer;
using Pi::ViewportWidget;

using Pi::Widget;
using Pi::WidgetEventData;
using Pi::WidgetObserver;
using Pi::WidgetReg;
using Pi::Window;
using Pi::World;
using Pi::WorldViewportWidget;

using Pi::Zero3D;
using Pi::Zone;

using Pi::PackFlag;

using Pi::WorldResult::Okay;

using Pi::TheNetworkMgr;

using namespace Pi::Math;

#include "Tankist.h"
#include "globals.h"
#include "Objects/ChaseCamera.h"
