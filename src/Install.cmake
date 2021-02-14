if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    if(WIN32)
        install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../out/debug"
    else()
        install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../../../out/debug"
    endif()
)
else()
    if(WIN32)
        install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../out/release"
    else()
        install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../../../out/release"
    endif()
)
endif()
