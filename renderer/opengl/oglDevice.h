#ifndef RENDERER_OPENGL_OGL_DEVICE_H_
#define RENDERER_OPENGL_OGL_DEVICE_H_

#include <core/debug/globlog.h>
#include <core/error.h>

#include <renderer/interface/DisplayInfo.h>

namespace radium
{


class oglDevice
{
public:
    oglDevice();
    ~oglDevice();

    ///
    /// @brief
    ///     Initialize the OpenGL Context
	///     
	///     				OpenGL - Platform Specific Implementations
	///     ┌────────────────────────────────────────────────────────────────────┐
	///     ├───────────────────────── Initialization ───────────────────────────┤
	///     │ init is defined in platform/<platform>/gl/glContext.cpp			 │
	///     │ _platform_init is defined here.								     │
	///     │																	 │
	///     │ _platform_init takes care of platform specific initialization,     │
	///     │  e.g. w/ wgl													     │													 
	///     │																	 │
	///     │ init takes care of platform dependent initialization -             │
	///     │ i.e glewInit, debug layer, glEnable(GL_something)					 │
	///     │																	 │
	///     │ init calls _platform_init										     │
	///     │																	 │
	///     ├─────────────────────────── Termination ────────────────────────────┤
	///     │																	 │
	///     │ `_platform_terminate` is defined in								 │
	///     │			platform/<platform>/gl/glContext.cpp				     │
	///     │ `terminate` calls _platform_terminate								 │
	///     │																	 │
	///     ├─────────────────────────── SwapBuffers ────────────────────────────┤
	///     │																	 │
	///     │ `swapBuffers` is defined in platform/<platform>/gl/glContext.cpp	 │
	///     │																	 │
	///     └────────────────────────────────────────────────────────────────────┘
	///     
	///		When porting oglDevice to a new windowing system/platform,
	///		you MUST provide OpenGL initialization for it.
	///		Assume that by the time _platform_* is called, we have a recent copy of 
	///		the display info
	///		
	///     
    Status init(DisplayInfo& dspi);


    void terminate();

private:
	/// platform specific initialization
	Status _platform_init();

	/// platform specific termination
	void _platform_terminate();


private:
	DisplayInfo m_displayinfo;


};


} // radium

#endif // RENDERER_OPENGL_OGL_DEVICE_H_