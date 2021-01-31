if(UNIX)

    target_link_libraries(${PROJECT_NAME} pthread)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
    )

endif()
