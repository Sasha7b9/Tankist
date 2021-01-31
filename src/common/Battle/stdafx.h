#pragma once

#define __restrict //-V2573


// PiEgnine

#include <Base/PiBase.h>
#include <Base/PiMemory.h>
#include <Graphics/PiRender.h>
#include <System/PiAudioCapture.h>
#include <Physics/PiCharacter.h>
#include <Graphics/PiGraphics.h>
#include <System/PiApplication.h>
#include <Geometry/PiMesh.h>
#include <Geometry/PiGizmo.h>
#include <Interface/PiConfiguration.h>
#include <Interface/PiToolWindows.h>
#include <Geometry/PiPrimitives.h>
#include <Controllers/PiController.h>
#include <Effects/PiParticles.h>
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
#include <Utilities/PiLogger.h>


#define SIZE_CHUNK_HEADER 4


// C++

#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>


// Third party

#ifdef WIN32
    #pragma warning(push, 0)
#endif

    #undef Bool
    #include <rapidjson/document.h>
    #include <sockpp/tcp_acceptor.h>
    #include <sockpp/tcp_connector.h>

#ifdef WIN32
    #pragma warning(pop)
#endif


// Tankist

#include "defines.h"

#include "FileSystem/_ConfigurationFile.h"
#include "FileSystem/_FileSystem.h"

#include "Game/_Cameras.h"
#include "Game/_GameWorld.h"

#include "Input/_Input.h"

#include "Network/_MasterServer.h"
#include "Network/Messages/_MessagesHangar.h"
#include "Network/Messages/_MessagesServer.h"

#include "Objects/_GameObjects.h"
#include "Objects/_GamePlayer.h"
#include "Objects/_Vehicle.h"

#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"
#include "Utils/_SystemFunctions.h"
#include "Utils/_SystemUtils.h"

#include "Server.h"

#include "globals.h"
