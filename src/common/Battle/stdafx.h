#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Network/Protocol.h>
#ifdef WIN32
#pragma warning(pop)
#endif


using namespace Urho3D;


#include "glob_engine.h"
#include "defines.h"

#include "Battle.h"
#include "Network/Server.h"
#include "Utils/_LogU.h"

#include "glob_game.h"
