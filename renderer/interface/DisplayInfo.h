#ifndef RENDERER_INTERFACE_DISPLAY_INFO_H_
#define RENDERER_INTERFACE_DISPLAY_INFO_H_

#include <core/types.h>

#ifdef RADIUM_PLATFORM_WIN32

namespace radium
{
///
/// @brief
///     Configuration for Graphics API on windows
///     Most graphics APIs will need a window handle/instance
///
///     This form should be filled out by the dispaly class (e.g. win32Display)
///     upon request.
///     Typically, this will be when initializing the Graphics API device.
///     e.g. 
/// @code
///     Display myDisplay;
///     myDisplay.create(100, 100, "clever, whimsical title");
///     
///     RenderDevice dev;
///     dev.init(myDisplay.getDisplayInfo());
/// @endcode
///     
/// @todo: see if (x,y) pos needs to be here too
/// 
struct DisplayInfo
{
    HWND windowHandle;
    HINSTANCE hInstance;

    U32 wwidth;
    U32 wheight;
    bool windowed;
};

} // radium
#endif // _WIN32


#endif // RENDERER_INTERFACE_DISPLAY_INFO_H_