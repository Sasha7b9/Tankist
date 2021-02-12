project (Battler)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/bass
                    ../../ThirdParty/opus/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)

add_definitions(-DURHO3D_LOGGING -DCLIENT)


if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
    add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
    add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
    add_compile_options(/wd4710)
    add_compile_options(/wd4711)
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
    add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
    add_compile_options(/wd28251)
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC                    ../../common_files/GameInput.*
                                                    *.h *.cpp)
file(GLOB GUI                                       GUI/*.*)
file(GLOB INPUT                                     Input/*.*)
file(GLOB NETWORK                                   Network/*.*
                                 ../../common_files/Network/Game/*.*)
file(GLOB SCENE                  ../../common_files/Scene/*.*)
file(GLOB SCENE_CAMERAS          ../../common_files/Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS          ../../common_files/Scene/Objects/*.*)
file(GLOB UTILS                  ../../common_files/Utils/_LogU.*)

source_group(src                 FILES ${SRC})
source_group(GUI                 FILES ${GUI})
source_group(Input               FILES ${INPUT})
source_group(Network             FILES ${NETWORK})
source_group(Network\\GameServer FILES ${NETWORK_GAMESERVER})
source_group(Scene               FILES ${SCENE})
source_group(Scene\\Cameras      FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects      FILES ${SCENE_OBJECTS})
source_group(Utils               FILES ${UTILS})

add_executable(${PROJECT_NAME} ${SRC} ${GUI} ${INPUT} ${NETWORK} ${NETWORK_GAMESERVER} ${SCENE} ${SCENE_CAMERAS}
    ${SCENE_OBJECTS} ${UTILS})

target_link_libraries(${PROJECT_NAME} opus)

include(../../RuntimeLibrary.cmake)

if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        target_link_libraries(${PROJECT_NAME} Urho3D_d)
    else()
        target_link_libraries(${PROJECT_NAME} Urho3D) 
    endif()
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
    target_link_libraries(${PROJECT_NAME} Bullet)
endif()

include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

include(../../Install.cmake)
