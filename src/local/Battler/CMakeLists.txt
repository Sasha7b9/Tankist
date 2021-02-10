project (Battler)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
include_directories(.
                    ../../common_files
                    ../../ThirdParty/bass
                    ../../ThirdParty/opus/include
                    ../../../../Urho3D/generated/debug/include
                    ../../../../Urho3D/generated/debug/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)
else()
include_directories(.
                    ../../common_files
                    ../../ThirdParty/bass
                    ../../ThirdParty/opus/include
                    ../../../../Urho3D/generated/release/include
                    ../../../../Urho3D/generated/release/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)
endif()

add_definitions(-DURHO3D_LOGGING)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4251)
    add_compile_options(/wd4355)    # 'this': used in base member initializer list
    add_compile_options(/wd4464)
    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
    add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared
                                    # inline
    add_compile_options(/wd4623)    # 'xxx': default constructor was implicitly defined as deleted 
    add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
    add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
    add_compile_options(/wd4710)
    add_compile_options(/wd4711)    #  function 'xxx' selected for automatic inline expansion
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
    add_compile_options(/wd4996)    # 
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    add_compile_options(/wd5219)
    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer implies
                                    # that compiler generated copy/move constructors and copy/move assignment operators are
                                    # not trivial
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC                RaycastVehicleDemo.*
                             Sample.*
                             stdafx.*
                             globals.*)
#file(GLOB AUDIO              Audio/*.*)
#file(GLOB AUDIO_CAPTURE      Audio/Capture/*.*)
file(GLOB GRAPHICS           Graphics/*.*)
#file(GLOB GUI                GUI/*.*)
file(GLOB GUI_ELEMENTS       GUI/Elements/*.*)
#file(GLOB NETWORK            Network/*.*)
file(GLOB OBJECTS            Objects/*.*)
file(GLOB UTILS              ../../common_files/Utils/_LogU.*)

source_group(src             FILES ${SRC})
#source_group(Audio           FILES ${AUDIO})
#source_group(Audio\\Capture  FILES ${AUDIO_CAPTURE})
source_group(Graphics        FILES ${GRAPHICS})
#source_group(GUI             FILES ${GUI})
source_group(GUI\\Elements   FILES ${GUI_ELEMENTS})
#source_group(Network         FILES ${NETWORK})
source_group(Objects         FILES ${OBJECTS})
source_group(Utils           FILES ${UTILS})

if(WIN32)
set_source_files_properties(stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)
endif()

add_executable(${PROJECT_NAME} ${SRC}
#${AUDIO}
#${AUDIO_CAPTURE}
${GRAPHICS}
#${GUI}
${GUI_ELEMENTS} ${AUDIO_CAPTURE}
#${NETWORK}
${OBJECTS}
${UTILS})

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

set(DIR $ENV{TANKIST_OUT_DIR})
include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

include(../../Install.cmake)
