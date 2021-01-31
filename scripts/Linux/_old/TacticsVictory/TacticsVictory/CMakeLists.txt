cmake_minimum_required(VERSION 3.10)

project(TacticsVictory)

set(COMMON_INCS "-I../../../Source/Source/TacticsVictory/TacticsVictory/ -I../../../Source/Source/PiEngine -I../../../Source/Source/PiEngine/OS_specific -I/usr/include -I/usr/lib/gcc/x86_64-linux-gnu/4.8.1/include")
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

source_group(src             REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/*.*)
source_group(GUI             REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/*.*)
source_group(GUI\\mutators   REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/mutators/*.*)
source_group(GUI\\panels     REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/panels/*.*)
source_group(GUI\\widgets    REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/widgets/*.*)
source_group(Input           REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/input/*.*)
source_group(Ojbects         REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/objects/*.*)
source_group(Resources       REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/resources/*.*)
source_group(Shaders         REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/shadres/*.*)
source_group(Sounds          REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/sounds/*.*)
source_group(Utils           REGULAR_EXPRESSION ../../../../Source/Source/TacticsVictory/TacticsVictory/utils/*.*)


file(GLOB SOURCES   ../../../../Source/Source/TacticsVictory/TacticsVictory/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/mutators/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/panels/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/GUI/widgets/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/input/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/objects/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/resources/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/shadres/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/sounds/*.*
                    ../../../../Source/Source/TacticsVictory/TacticsVictory/utils/*.*
)


add_executable(TacticsVictory  ${SOURCES})

target_link_libraries(TacticsVictory PiEngine pthread)

set_target_properties(TacticsVictory PROPERTIES
	LINKER_LANGUAGE CXX
)

