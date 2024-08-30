
if(API_OPENGL)
    set(WINDOWS_SOURCES 
        "platform/windows/gl/glPlatformInit.cpp"
    )
endif()

set(WINDOWS_SOURCES ${WINDOWS_SOURCES}
    "platform/windows/debug/seh.cpp"
    "platform/windows/thread/mutex.cpp"    
    "platform/windows/thread/thread.cpp"
    "platform/windows/file.cpp"
    "platform/windows/timer.cpp"
    "platform/windows/win32Display.cpp"
    PARENT_SCOPE
)
