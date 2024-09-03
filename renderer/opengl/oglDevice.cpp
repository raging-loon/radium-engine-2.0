#include "oglDevice.h"

#include <GL/glew.h>
#include <renderer/opengl/oglDebug.h>
#include <core/debug/globlog.h>
#include <renderer/interface/Buffer.h>
#include <renderer/interface/Interface.h>
#include <renderer/opengl/shader/oglShaderFactory.h>

using namespace radium;

oglDevice::oglDevice()
#ifdef RADIUM_PLATFORM_WIN32
    : m_hDevCtx(nullptr), m_hGlCtx(nullptr)
#endif // RADIUM_PLATFORM_WIN32
    , m_bufferFactory{}

{
}

oglDevice::~oglDevice()
{
    terminate();
}

Status oglDevice::init(DisplayInfo& dspi)
{
    m_displayinfo = dspi;

    // platform-specific initialization
    Status pInitStatus = _platform_init();
    if (pInitStatus != OK)
        return pInitStatus;


    // init glew
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        ENGINE_CRITICAL("[GL] Failed to initialize GLEW: %s", (char*)glewGetErrorString(err));
        return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
    }

    ENGINE_INFO("[GL] Intialized GLEW: %s", (char*)glewGetString(GLEW_VERSION));

#if RADIUM_DEBUG_BUILD
    // add debug support
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)oglErrorCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif // RADIUM_DEBUG_BUILD

    glEnable(GL_DEPTH_TEST);
    m_bufferFactory.init();
    return OK;
}

void oglDevice::terminate()
{
    _platform_terminate();
}

rtl::shared_ptr<Buffer> oglDevice::createBuffer(BufferDescription& bd)
{
    return m_bufferFactory.createBuffer(bd);
}

Shader* oglDevice::createShader(ShaderDescription& sd)
{
    oglShaderFactory osf;
    GLuint spid = osf.createShaderProgram(sd);
    if (spid == GL_INVALID_VALUE)
        return nullptr;
    return new Shader(spid);
}

Texture* oglDevice::createTexture(TextureDescription& td)
{
    if (!td.data) return nullptr;
    GLuint texid;
    glGenTextures(1, &texid);

    glBindTexture(GL_TEXTURE_2D, texid);

    GLint samplestate;
    switch (td.sampleState)
    {
        case TEXTURE_SAMPLER_REPEAT:
            samplestate = GL_REPEAT;
            break;
        case TEXTURE_SAMPLER_CLAMP:
            samplestate = GL_CLAMP;
            break;
        case TEXTURE_SAMPLER_MIRROR:
            samplestate = GL_MIRRORED_REPEAT;
            break;
        default:
            ENGINE_ERROR("Invalid Texture Sample State passed to oglDevice::createTexture: 0x%0x", td.sampleState);
            glDeleteTextures(1, &texid);
            return nullptr;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplestate);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, samplestate);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, td.width, td.height, 0, GL_RGB, GL_UNSIGNED_BYTE, td.data);

    // todo: config for this: glGenerateMipMap

    return new oglTexture(texid);

}

