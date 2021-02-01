cmake_minimum_required(VERSION 2.4)

# Libraries linked via full path no longer produce linker search paths
cmake_policy (SET CMP0003 NEW)

# link_directories() treats paths relative to the source dir.
cmake_policy (SET CMP0015 NEW)

# MSVC runtime library flags are selected an abstraction
cmake_policy(SET CMP0091 NEW)


project (TankistU3D)

set (TARGET_NAME TankistU3D)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)                                              # Для отладочной версии

    add_definitions(-DPiDEBUG -DDEBUG)

    if(WIN32)
        link_directories(../../generated/debug/Engine/PiEngine/Debug
                         ../../generated/debug/Engine/WorldEditor/Debug
                         ../../generated/debug/Engine/Plugins/TextureTool/Debug)
    else()
        link_directories(../generated/debug/ThirdParty/bin)
        add_definitions(-g -Og)
    endif()

elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)                                        # Для релизной версии

    add_definitions(-DPiOPTIMIZED)
    
    if(WIN32)
        link_directories(../../generated/release/Engine/PiEngine/Release
                         ../../generated/release/Engine/WorldEditor/Release
                         ../../generated/release/Engine/Plugins/TextureTool/Release)
    else()
        link_directories(../generated/release/ThirdParty/bin)
    endif()

endif()

if(WIN32)
    add_definitions(-DPiWINDOWS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall /std:c++17")
else()
    add_definitions(-DPiLINUX)
    add_definitions(-m64 -msse -msse2 -std=c++17 -pthread -ffast-math -fno-strict-aliasing -fno-rtti -fmax-errors=1 -Wall)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
define_property(
    TARGET
    PROPERTY FOLDER
    INHERITED
    BRIEF_DOCS "Set the folder name."
    FULL_DOCS "Use to organize targets in an IDE."
)

function(add_subdirectory_with_folder _folder_name _folder)
    add_subdirectory(${_folder} ${ARGN})
    set_property(DIRECTORY "${_folder}" PROPERTY FOLDER "${_folder_name}")
endfunction()

if(WIN32)
   add_subdirectory_with_folder("local" local/Battler)
   add_subdirectory_with_folder("local" local/Client)
   add_subdirectory_with_folder("local" local/Tankist)
   add_subdirectory_with_folder("local" local/Updater)
endif()

add_subdirectory_with_folder("remote" remote/DataBase)
add_subdirectory_with_folder("remote" remote/Master)

add_subdirectory_with_folder("common" common/Battle)
add_subdirectory_with_folder("common" common/Configurator)
add_subdirectory_with_folder("common" common/Hangar)
add_subdirectory_with_folder("common" common/Monitor)
add_subdirectory_with_folder("common" common/Uploader)
