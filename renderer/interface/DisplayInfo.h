#ifndef RENDERER_INTERFACE_DISPLAY_INFO_H_
#define RENDERER_INTERFACE_DISPLAY_INFO_H_

#include <core/types.h>
namespace radium
{

#ifdef _WIN32

struct DisplayInfo
{
    HWND windowHandle;
    HINSTANCE hInstance;

    U32 wwidth;
    U32 wheight;
    bool windowed;
};

#endif // _WIN32


} // radium
#endif // RENDERER_INTERFACE_DISPLAY_INFO_H_