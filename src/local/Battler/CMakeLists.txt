project (Battler)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/debug/include
                    ../../../../Urho3D/generated/debug/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)
else()
include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/release/include
                    ../../../../Urho3D/generated/release/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_compile_options(/wd4355)    # 'this': used in base member initializer list
add_compile_options(/wd4464)
add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared inline
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
add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer implies that compiler generated copy/move constructors and copy/move assignment operators are not trivial

file(GLOB SRC                ../../common_files/_defines.h
                                                *.h
                                                *.cpp)
file(GLOB AUDIO_CAPTURE      Auto/Capture/*)
file(GLOB UTILS              ../../common_files/Utils/_LogU.*)
                             
source_group(src             FILES ${SRC})
source_group(Audio\\Capture  FILES ${AUDIO_CAPTURE})
source_group(Utils           FILES ${UTILS})

set_source_files_properties(stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)

add_executable(${PROJECT_NAME} ${SRC} ${AUDIO_CAPTURE})

if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        target_link_libraries(${PROJECT_NAME} Urho3D_d)
    else()
        target_link_libraries(${PROJECT_NAME} Urho3D) 
    endif()
else()
    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    else()
    endif()
endif()
