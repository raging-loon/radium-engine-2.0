#include "oglDevice.h"

#include <GL/glew.h>
#include <renderer/opengl/oglDebug.h>

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
