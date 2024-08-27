#if defined(RADIUM_PLATFORM_WIN32) && defined(RADIUM_API_OPENGL) && defined(_WIN32)

#include <renderer/opengl/oglDevice.h>
#include <core/error.h>

#include <Windows.h>

// if this include is giving you an error
// in your IDE, it is safe to ignore
#include <GL/glew.h>
#include <GL/wglext.h>
#include <wingdi.h>

using radium::oglDevice;
using radium::Status;


Status oglDevice::_platform_init()
{
    assert(m_displayinfo.windowHandle && m_displayinfo.hInstance);


	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// nSize
		1,								// nVersion
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // dwFlags
		PFD_TYPE_RGBA,					// iPixelTpype
		32,								// cColorBits
		0, 0, 0, 0, 0, 0,				// RGBA Bits/Shift
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC hdDevCtx = GetDC(m_displayinfo.windowHandle);

	m_displayinfo.hDevCtx = hdDevCtx;

	int pixelFormat = ChoosePixelFormat(hdDevCtx, &pfd);

	SetPixelFormat(hdDevCtx, pixelFormat, &pfd);

	HGLRC tempContext = wglCreateContext(hdDevCtx);

	if (!tempContext)
	{
		ENGINE_CRITICAL("[WGL]: Failed to create context");
		return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
	}

	wglMakeCurrent(hdDevCtx, tempContext);

#ifdef RADIUM_DEBUG_BUILD
	///
	/// This might seem hacky. That is because it is.
	/// According to Khronos and Microsoft documentation,
	/// this is the only way to do it }:(
	/// 
	/// Steps to create a debug context:
	///		1. Create a non-debug context
	///		2. use the non-debug context
	///		3. load the debug extension using this context
	///		4. create a debug context
	///		5. delete the old-non-debug context
	///		6. use the debug context
	/// 


	int debugAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		0
	};

	// load the extension
	auto* wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if (!wglCreateContextAttribsARB)
	{
		ENGINE_CRITICAL("[WGL]: Failed to load debug extension! (WglCreateContextAttribsARB)");
		return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
	}
	// make a new debug context
	m_displayinfo.hGlCtx = wglCreateContextAttribsARB(hdDevCtx, 0, debugAttribs);

	if (!m_displayinfo.hGlCtx)
	{
		ENGINE_CRITICAL("[WGL]: Failed to create OpenGL Debug Context");
		return ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE;
	}
	// delete the old context
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(tempContext);

	// use the new debug context
	wglMakeCurrent(hdDevCtx, m_displayinfo.hGlCtx);

	ENGINE_INFO("[WGL]: Created OpenGL Debug Context: {}", (char*)(glGetString(GL_VERSION)));

#else
	// otherwise do nothing
	m_displayinfo.hGlCtx = tempContext;
	ENGINE_INFO("[WGL]: Created OpenGL context: {}", (char*)(glGetString(GL_VERSION)));
#endif // RADIUM_DEBUG_BUILD
	
	return OK;

}



#endif // exclude 