cmake_minimum_required(VERSION 3.10)

project(PiEngine)

set(COMMON_INCS "-I../../Source/ThirdParty/SLikeNet -I../../Source/Source/PiEngine/OS_specific -I../../Source/Source/PiEngine -I/usr/include -I/usr/lib/gcc/x86_64-linux-gnu/4.8.1/include")

set(COMMON_CFLAGS "-m64 -msse -msse2 -std=c++11 -pthread -ffast-math -fno-strict-aliasing -fno-exceptions -fno-rtti")
set(COMMON_LFLAGS "-fno-exceptions -fno-rtti")

set(DEBUG_CFLAGS "-DPiDEBUG -g -Og")
set(ENGINE_FLAGS "-DPiLINUX -DPiENGINEMODULE -shared -fPIC")

set(WARNINGS "-Wall -Wno-unused-function -Wno-switch -Wno-multichar -Wno-char-subscripts -Wno-enum-compare -Wno-uninitialized -Wno-non-virtual-dtor"
             "-Wno-delete-non-virtual-dtor -Wno-sign-compare -Wno-invalid-offsetof -Wno-deprecated-declarations -Wno-unused-result -Wno-array-bounds"
             "-Wno-maybe-uninitialized")


set(CFLAGS ${COMMON_INCS} ${COMMON_CFLAGS} ${WARNINGS} ${DEBUG_CFLAGS} ${COMMON_LFLAGS} ${ENGINE_FLAGS})
add_definitions(${CFLAGS})

file(GLOB BASE        "../../../Source/Source/PiEngine/Base/*.cpp")
file(GLOB CONTAINER   "../../../Source/Source/PiEngine/Contrainer/*.cpp")
file(GLOB CONTROLLERS "../../../Source/Source/PiEngine/Controllers/*.cpp")
file(GLOB EFFECTS     "../../../Source/Source/PiEngine/Effects/*.cpp")
file(GLOB GEOMETRY    "../../../Source/Source/PiEngine/Geometry/*.cpp")
file(GLOB GRAPHICS    "../../../Source/Source/PiEngine/Graphics/*.cpp")
file(GLOB INTERFACE   "../../../Source/Source/PiEngine/Interface/*.cpp")
file(GLOB IO          "../../../Source/Source/PiEngine/IO/*.cpp")
file(GLOB MATH        "../../../Source/Source/PiEngine/Math/*.cpp")
file(GLOB NETWORK     "../../../Source/Source/PiEngine/Network/*.cpp")
file(GLOB OBJECTS     "../../../Source/Source/PiEngine/Objects/*.cpp")
file(GLOB PHYSICS     "../../../Source/Source/PiEngine/Physics/*.cpp")
file(GLOB PLUGINS     "../../../Source/Source/PiEngine/Plugins/*.cpp")
file(GLOB RESOURCE    "../../../Source/Source/PiEngine/Resource/*.cpp")
file(GLOB SRC         "../../../Source/Source/PiEngine/*.cpp")
file(GLOB SYSTEM      "../../../Source/Source/PiEngine/System/PiApplication.cpp"
                      "../../../Source/Source/PiEngine/System/PiAudioCapture.cpp"
                      "../../../Source/Source/PiEngine/System/PiCommands.cpp"
                      "../../../Source/Source/PiEngine/System/PiCompression.cpp"
                      "../../../Source/Source/PiEngine/System/PiDisplay.cpp"
                      "../../../Source/Source/PiEngine/System/PiEngine.cpp"
                      "../../../Source/Source/PiEngine/System/PiImage.cpp"
                      "../../../Source/Source/PiEngine/System/PiInput.cpp"
                      "../../../Source/Source/PiEngine/System/PiMain.cpp"
                      "../../../Source/Source/PiEngine/System/PiMessages.cpp"
                      "../../../Source/Source/PiEngine/System/PiNetwork.cpp"
                      "../../../Source/Source/PiEngine/System/PiSound.cpp"
                      "../../../Source/Source/PiEngine/System/PiStringTable.cpp"
                      "../../../Source/Source/PiEngine/System/PiThreads.cpp"
                      "../../../Source/Source/PiEngine/System/PiTime.cpp"
                      "../../../Source/Source/PiEngine/System/PiVariables.cpp"
                      )
file(GLOB UTILITIES   "../../../Source/Source/PiEngine/Utilities/*.cpp")
file(GLOB WORLD       "../../../Source/Source/PiEngine/World/*.cpp")

add_library(PiEngine SHARED ${BASE}
                            ${CONTAINER}
                            ${CONTROLLERS}
                            ${EFFECTS}
                            ${GEOMETRY}
                            ${GRAPHICS}
                            ${INTERFACE}
                            ${IO}
                            ${MATH}
                            ${NETWORK}
                            ${OBJECTS}
                            ${PHYSICS}
                            ${PLUGINS}
                            ${RESOURCE}
                            ${SRC}
                            ${SYSTEM}
                            ${UTILITIES}
                            ${WORLD}
)

target_link_libraries(PiEngine GL X11 Xrandr asound)

set_target_properties(PiEngine PROPERTIES
	LINKER_LANGUAGE CXX
)

