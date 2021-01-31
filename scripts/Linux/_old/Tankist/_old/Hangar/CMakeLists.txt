cmake_minimum_required(VERSION 3.10)

project(Hangar)

set(COMMON_INCS "-I../../../Source/Source/Tankist/ -I../../../Source/Source/Tankist/remote/Hangar/ -I../../../Source/Source/PiEngine -I../../../Source/Source/PiEngine/OS_specific -I/usr/include -I/usr/lib/gcc/x86_64-linux-gnu/4.8.1/include")
add_definitions(-DPiLINUX -DPiDEBUG)
set(COMMON_CFLAGS "-std=c++11 -m64 -msse -msse2 -pthread -ffast-math -fno-strict-aliasing -fno-exceptions -fno-rtti")
set(PLUGIN_CFLAGS "-fPIC")
set(WARNINGS "-Wno-unused-function -Wno-switch -Wno-multichar -Wno-char-subscripts -Wno-uninitialized -Wno-non-virtual-dtor -Wno-delete-non-virtual-dtor" 
             "-Wno-sign-compare -Wno-invalid-offsetof -Wno-deprecated-declarations -Wno-unused-result -Wno-array-bounds -Wno-maybe-uninitialized -Wno-multichar"
             " -Wno-enum-compare -Wno-write-strings"
)
set(DEBUG_CFLAGS "-g -Og")
#set(COMMON_LFLAGS "-fno-exceptions -fno-rtti")

set(CFLAGS ${COMMON_INCS}  ${INCDIR} ${COMMON_DEFINES} ${COMMON_CFLAGS} ${WARNINGS} ${DEBUG_CFLAGS} ${COMMON_LFLAGS})
add_definitions(${CFLAGS})

source_group(src             REGULAR_EXPRESSION ../../../../Source/Source/Tankist/remote/Hangar/*)
source_group(Network         FILES              ../../../../Source/Source/Tankist/common/Network/MessagesHangar.h
                                                ../../../../Source/Source/Tankist/common/Network/MessagesHangar.cpp
                                                ../../../../Source/Source/Tankist/common/Network/MessagesServer.h
                                                ../../../../Source/Source/Tankist/common/Network/MessagesServer.cpp
                                                ../../../../Source/Source/Tankist/remote/Hangar/Network/HandlersNetworkEventsHangar.cpp
                                                ../../../../Source/Source/Tankist/remote/Hangar/Network/MainServer.h
                                                ../../../../Source/Source/Tankist/remote/Hangar/Network/MainServer.cpp)

file(GLOB SOURCES   ../../../../Source/Source/Tankist/remote/Hangar/*

                    ../../../../Source/Source/Tankist/common/Network/MessagesHangar.h
                    ../../../../Source/Source/Tankist/common/Network/MessagesHangar.cpp
                    ../../../../Source/Source/Tankist/common/Network/MessagesServer.h
                    ../../../../Source/Source/Tankist/common/Network/MessagesServer.cpp
                    ../../../../Source/Source/Tankist/remote/Hangar/Network/HandlersNetworkEventsHangar.cpp
                    ../../../../Source/Source/Tankist/remote/Hangar/Network/MainServer.h
                    ../../../../Source/Source/Tankist/remote/Hangar/Network/MainServer.cpp
)

add_executable(Hangar  ${SOURCES})

target_link_libraries(Hangar PiEngine pthread)

set_target_properties(Hangar PROPERTIES
	LINKER_LANGUAGE CXX
)

