#pragma once

#define __restrict //-V2573


// PiEngine

#include <Base/PiBase.h>
#include <Base/PiDefines.h>

#include <Graphics/PiGraphics.h>

#include <Interface/PiConfiguration.h>
#include <Interface/PiInterface.h>
#include <Interface/PiWidgets.h>

#include <Resource/PiConfigData.h>

#include <System/PiApplication.h>
#include <System/PiEngine.h>
#include <System/PiMain.h>

#include <Utilities/PiString.h>

#include <World/PiWorld.h>


// C++

#include <cstdarg>
#include <cstdlib>
#include <iostream>
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

#include "Tankist.h"

#include "FileSystem/_ConfigurationFile.h"
#include "FileSystem/_FileSystem.h"

#include "Interface/MainWindow.h"
#include "Interface/Settings.h"

#include "Network/_MasterServer.h"

#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"
#include "Utils/_SystemFunctions.h"
#include "Utils/_SystemUtils.h"

#include "globals.h"
