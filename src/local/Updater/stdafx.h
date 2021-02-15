// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// C++

#include <cstdarg>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>


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

#include "Network/Other/_SocketsTCP.h"

#include "Utils/_Log.h"
#include "Utils/_StringUtils.h"
#include "Utils/_SystemFunctions.h"
#include "Utils/_SystemUtils.h"
