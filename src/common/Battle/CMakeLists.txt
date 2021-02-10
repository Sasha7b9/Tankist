project (Battle)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp_/sockpp/include
                    ../../ThirdParty/rapidjson_/rapidjson/include)


set(USE_SOCKPP 1)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    
    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

#    add_compile_options(/wd4355)    # 'this': used in base member initializer list
#    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
#    add_compile_options(/wd4595)    # 'operator 'xxx'': non-member operator new or delete functions may not be declared inline
#    add_compile_options(/wd4623)    # 'xxx': default constructor was implicitly defined as deleted 
#    add_compile_options(/wd4625)    # 'xxx': copy constructor was implicitly defined as deleted
#    add_compile_options(/wd4626)    # 'xxx': assignment operator was implicitly defined as deleted
#    add_compile_options(/wd4710)    # 'function': function not inlined
#    add_compile_options(/wd4711)    #  function 'xxx' selected for automatic inline expansion
#    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
#    add_compile_options(/wd4996)    # 
#    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
#    add_compile_options(/wd5027)    # 'xxx': move assignment operator was implicitly defined as deleted
#    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer implies that compiler generated copy/move constructors and copy/move assignment operators are not trivial
    
else()

    add_definitions(-Wno-unused-function # 'xxx' defined but not used
                    -Wno-enum-compare    # comparison between 'xxx' and 'yyy'
                    -Wno-multichar       # multi-character character constant
                    -Wno-cpp             # the 'xxx' header is deprecated and well be removed
    )

endif()

file(GLOB SRC              ../../common_files/_defines.h
                                              *.h *.cpp)

source_group(src               FILES ${SRC})

add_executable(${PROJECT_NAME} ${SRC})

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
