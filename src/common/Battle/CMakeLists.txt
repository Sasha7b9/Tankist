project (Battle)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/bass
                    ../../ThirdParty/opus/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty
                    ../../../../Urho3D/Source
                    ../../../../Urho3D/Source/ThirdParty
                    ../../../../Urho3D/Source/ThirdParty/Bullet/src)


add_definitions(-DURHO3D_LOGGING -DSERVER)


if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    
    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

#    add_compile_options(/wd4355)    # 'this': used in base member initializer list
    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
#    add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared
                                    # inline
#    add_compile_options(/wd4623)    # 'xxx': default constructor was implicitly defined as deleted 
    add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
    add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
    add_compile_options(/wd4710)    # 'function': function not inlined
    add_compile_options(/wd4711)    #  function 'xxx' selected for automatic inline expansion
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
#    add_compile_options(/wd4996)    # 
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
#    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer
                                    # implies that compiler generated copy/move constructors and copy/move assignment
                                    # operators are not trivial
    add_compile_options(/wd28251)
    
else()

    add_definitions(-Wno-unused-function # 'xxx' defined but not used
                    -Wno-enum-compare    # comparison between 'xxx' and 'yyy'
                    -Wno-multichar       # multi-character character constant
                    -Wno-cpp             # the 'xxx' header is deprecated and well be removed
    )

endif()

file(GLOB SRC                    ../../common_files/_defines.h
                                                    *.h *.cpp)
file(GLOB NETWORK                                   Network/*.*
                                 ../../common_files/Network/Game/*.*)
file(GLOB SCENE                  ../../common_files/Scene/*.*)
file(GLOB SCENE_OBJECTS          ../../common_files/Scene/Objects/*.*)
file(GLOB UTILS                  ../../common_files/Utils/_LogU.*)

source_group(src                 FILES ${SRC})
source_group(Network             FILES ${NETWORK})
source_group(Network\\GameServer FILES ${NETWORK_GAMESERVER})
source_group(Scene               FILES ${SCENE})
source_group(Scene\\Objects      FILES ${SCENE_OBJECTS})
source_group(Utils               FILES ${UTILS})

add_executable(${PROJECT_NAME} ${SRC} ${NETWORK} ${NETWORK_GAMESERVER} ${SCENE} ${SCENE_OBJECTS} ${UTILS})

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
