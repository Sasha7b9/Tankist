#pragma once

#define __restrict //-V2573


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
#include <vector>


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
