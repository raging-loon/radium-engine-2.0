

if(API_OPENGL)

    set(GRAPHICS_SOURCES
        "renderer/opengl/oglDevice.cpp"
        "renderer/opengl/oglDebug.cpp"
        "renderer/opengl/oglBuffer.cpp"
        "renderer/opengl/oglTexture.cpp"
        "renderer/opengl/oglBufferFactory.cpp"
        "renderer/opengl/shader/oglShader.cpp"
        "renderer/opengl/shader/oglShaderFactory.cpp"
        "renderer/opengl/shader/oglShaderPreprocessor.cpp"
        "thirdparty/glew/src/glew.c"
    )

    set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES}
        "thirdparty/glew/include"
        PARENT_SCOPE
    )

    if(WIN32)
        set(GRAPHICS_API_LIBS ${GRAPHICS_API_LIBS}
            opengl32.lib
            PARENT_SCOPE
        )
    endif()
endif()

set(GRAPHICS_SOURCES ${GRAPHICS_SOURCES} PARENT_SCOPE)

