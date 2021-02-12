project (Client)

include_directories(.
                    ../../common_files
                    ../../../../Source/PiEngine
                    ../../ThirdParty/sockpp_/sockpp/include
                    ../../ThirdParty/rapidjson_/rapidjson/include)

set(USE_SOCKPP 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_compile_options(/wd4514)
add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared inline
add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
add_compile_options(/wd4710)
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd4820)
add_compile_options(/wd4996)    # 
add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer implies that compiler generated copy/move constructors and copy/move assignment operators are not trivial

file(GLOB SRC        ../../common_files/_defines.h
                                        *.cpp
                                        *.h)
file(GLOB FILESYSTEM ../../common_files/FileSystem/_ConfigurationFile.*
                     ../../common_files/FileSystem/_FileSystem.*)
file(GLOB NETWORK    ../../common_files/Network/Other/_HangarServer.*
                     ../../common_files/Network/Other/_SocketsTCP.*)
file(GLOB UTILS      ../../common_files/Utils/_Log.*
                     ../../common_files/Utils/_StringUtils.*
                     ../../common_files/Utils/_SystemFunctions.*
                     ../../common_files/Utils/_SystemUtils.*)

source_group(src        FILES ${SRC})
source_group(FileSystem FILES ${FILESYSTEM})
source_group(Network    FILES ${NETWORK})
source_group(Utils      FILES ${UTILS})

set_source_files_properties(stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)

add_executable(${PROJECT_NAME} ${SRC} ${FILESYSTEM} ${NETWORK} ${UTILS})

include(../../RuntimeLibrary.cmake)

include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

include(../../LinkLibraries.cmake)        # Подключаем дополнительные библиотеки
include(../../Install.cmake)
