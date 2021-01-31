cmake_minimum_required(VERSION 3.10)

project (PiEngine2 CXX)

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


add_subdirectory(PiEngine)

add_subdirectory_with_folder("TacticsVictory" TacticsVictory/TacticsVictory)
add_subdirectory_with_folder("Server" Tankist/Server)
add_subdirectory_with_folder("Server" Tankist/Hangar)
