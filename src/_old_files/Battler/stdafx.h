#pragma once


// C++

#undef alignas
#include <cstdarg>
#include <cstdio>
#include <map>
#include <mutex>
#include <sstream>
#include <string>


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

#include "Client.h"

#include "FileSystem/_ConfigurationFile.h"
#include "FileSystem/_FileSystem.h"

#include "Game/_Cameras.h"
#include "Game/_GameWorld.h"

#include "Input/_Input.h"

#include "Interface/HangarWidgets.h"
#include "Interface/Settings.h"

#include "Network/MainServer.h"
#include "Network/_MasterServer.h"
#include "Network/Messages/_MessagesHangar.h"
#include "Network/Messages/_MessagesServer.h"

#include "Objects/_GamePlayer.h"
#include "Objects/_Vehicle.h"

#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"
#include "Utils/_SystemFunctions.h"
#include "Utils/_SystemUtils.h"

#include "globals.h"

