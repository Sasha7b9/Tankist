project (DataBase)

include_directories(.
                    )

if(WIN32)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

endif()

file(GLOB SRC   *.cpp *.h)

source_group(src        FILES ${SRC})

add_executable(${PROJECT_NAME} ${SRC})

include(../../RuntimeLibrary.cmake)      # Исключаем зависимости от динамических библиотек VS времени выполнения релизной версии

include(../../LinkLibraries.cmake)          # Подключаем дополнительные библиотеки

if(WIN32)
    include(../../CopyToDirEXE.cmake)
    include(../../SetWorkingDirectory.cmake)
endif()

include(../../Install.cmake)
