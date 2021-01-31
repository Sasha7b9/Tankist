#pragma once


// PiEngine

#include <Base/PiBase.h>

#include <System/PiApplication.h>
#include <System/PiEngine.h>
#include <System/PiMain.h>

#include <Utilities/PiLogger.h>
#include <Utilities/PiString.h>


// C++

#include <cstdarg>
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

#include "FileSystem/_FileSystem.h"

#include "Network/Messages/_MessagesHangar.h"
#include "Network/Messages/_MessagesServer.h"

#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"
#include "Utils/_SystemFunctions.h"
#include "Utils/_SystemUtils.h"

#include "globals.h"
