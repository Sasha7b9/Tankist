if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../../../Tankist/out/debug"
)
else()
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../../../Tankist/out/release"
)
endif()
