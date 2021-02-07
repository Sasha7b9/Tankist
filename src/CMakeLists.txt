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

    add_definitions(-DDEBUG)

    if(WIN32)
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/debug/ThirdParty/sockpp_/sockpp/Debug
                         ../../Urho3D/generated/debug/lib
                         ThirdParty/bass
                         ThirdParty/opus/generated/Release)
    else()
        link_directories(../generated/debug/ThirdParty/bin
                         ../../Urho3D/generated/debug/lib
                         ThirdParty/opus/generated)
        add_definitions(-g -Og)
    endif()

elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)                                        # Для релизной версии

    if(WIN32)
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/release/ThirdParty/sockpp_/sockpp/Release
                         ../../Urho3D/generated/release/lib
                         ThirdParty/bass
                         ThirdParty/opus/generated/Release)
    else()
        link_directories(../generated/release/ThirdParty/bin
                         ../../Urho3D/generated/release/lib
                         ThirdParty/opus/generated)
    endif()

endif()

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall /std:c++17")
else()
    add_definitions(-m64 -msse -msse2 -std=c++17 -pthread -ffast-math -fno-strict-aliasing -fmax-errors=1 -Wall)
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
   add_subdirectory_with_folder("local" local/Client)
   add_subdirectory_with_folder("local" local/Tankist)
   add_subdirectory_with_folder("local" local/Updater)
endif()

add_subdirectory_with_folder("local" local/Battler)

add_subdirectory_with_folder("remote" remote/DataBase)
add_subdirectory_with_folder("remote" remote/Master)

add_subdirectory_with_folder("common" common/Configurator)
add_subdirectory_with_folder("common" common/Hangar)
add_subdirectory_with_folder("common" common/Monitor)
add_subdirectory_with_folder("common" common/Uploader)
