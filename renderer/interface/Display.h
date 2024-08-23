#ifndef RENDERER_INTERFACE_DISPLAY_H_
#define RENDERER_INTERFACE_DISPLAY_H_

#ifdef _WIN32

#include <platform/windows/win32Display.h>
namespace radium { using Display = radium::win32Display; }


#endif // _WIN32




#endif // RENDERER_INTERFACE_DISPLAY_H_