project (Battle)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp_/sockpp/include
                    ../../ThirdParty/rapidjson_/rapidjson/include)


set(USE_SOCKPP 1)

include(../../AddPathsToLibraries.cmake)    # Добавляем пути к подключаемым библиотекам


if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    
    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    add_compile_options(/wd4355)    # 'this': used in base member initializer list
    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
    add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared inline
    add_compile_options(/wd4623)    # 'xxx': default constructor was implicitly defined as deleted 
    add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
    add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
    add_compile_options(/wd4710)    # 'function': function not inlined
    add_compile_options(/wd4711)    #  function 'xxx' selected for automatic inline expansion
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
    add_compile_options(/wd4996)    # 
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer implies that compiler generated copy/move constructors and copy/move assignment operators are not trivial
    
else()

    add_definitions(-Wno-unused-function # 'xxx' defined but not used
                    -Wno-enum-compare    # comparison between 'xxx' and 'yyy'
                    -Wno-multichar       # multi-character character constant
                    -Wno-cpp             # the 'xxx' header is deprecated and well be removed
    )

endif()

file(GLOB SRC              ../../common_files/_defines.h
                                              globals.*
                                              Server.*
                                              stdafx.*
                                              defines.*)
file(GLOB FILE_SYSTEM      ../../common_files/FileSystem/_ConfigurationFile.*
                           ../../common_files/FileSystem/_FileSystem.*)
file(GLOB GAME             ../../common_files/Game/_Cameras.*
                           ../../common_files/Game/_GameWorld.*)
file(GLOB _GUI                                GUI/*)
file(GLOB INPUT            ../../common_files/Input/_Input.h)
file(GLOB NETWORK                             Network/HandlersNetworkEventsServer.cpp
                                              Network/MainServer.*
                           ../../common_files/Network/_MasterServer.*
                           ../../common_files/Network/_SocketsTCP.*)
file(GLOB NETWORK_MESSAGES ../../common_files/Network/Messages/_MessagesServer.*)
file (GLOB OBJECTS         ../../common_files/Objects/_GameObjects.*
                           ../../common_files/Objects/_Vehicle.*)
file(GLOB UTILS            ../../common_files/Utils/_Log.*
                           ../../common_files/Utils/_StringUtils.*
                           ../../common_files/Utils/_SystemFunctions.*
                           ../../common_files/Utils/_SystemUtils.*)

source_group(src               FILES ${SRC})
source_group(FileSystem        FILES ${FILE_SYSTEM})
source_group(Game              FILES ${GAME})
source_group(GUI               FILES ${_GUI})
source_group(Input             FILES ${INPUT})
source_group(Network           FILES ${NETWORK})
source_group(Network\\Messages FILES ${NETWORK_MESSAGES})
source_group(Objects           FILES ${OBJECTS})
source_group(Utils             FILES ${UTILS})

add_executable(${PROJECT_NAME} ${SRC} ${FILE_SYSTEM} ${GAME} ${_GUI} ${INPUT} ${NETWORK} ${NETWORK_MESSAGES} ${OBJECTS} ${UTILS})

include(../../RuntimeLibrary.cmake)

set(DIR $ENV{TANKIST_OUT_DIR})
include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

include(../../LinkLibraries.cmake)          # Подключаем дополнительные библиотеки
include(../../Install.cmake)
