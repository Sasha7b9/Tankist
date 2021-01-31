
if(USE_SOCKPP)

    if(${CMAKE_BUILD_TYPE} STREQUAL Release)        # Для релизной версии
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/release/ThirdParty/sockpp_/sockpp/Release)
    elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/debug/ThirdParty/sockpp_/sockpp/Debug)
    endif()

endif()


if(USE_CPPFS)

    if(${CMAKE_BUILD_TYPE} STREQUAL Release)        # Для релизной версии
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/release/ThirdParty/cppfs_/cppfs/Release)
    elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        link_directories($ENV{PROJECT_TANKIST_DIR}/generated/debug/ThirdParty/cppfs_/cppfs/Debug)
    endif()

endif()
