if(WIN32)
    add_subdirectory(windows)
    
    set(PLATFORM_SOURCES
        ${WINDOWS_SOURCES}
        PARENT_SCOPE
    )
    message(${WINDOWS_SOURCES})
endif()