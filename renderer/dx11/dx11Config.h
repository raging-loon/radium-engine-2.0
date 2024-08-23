#ifndef RENDERER_DX11_DX11_CONFIG_H_
#define RENDERER_DX11_DX11_CONFIG_H_

#include <windows.h>
#include <core/types.h>
namespace radium
{

struct RenderDeviceInitCfg
{
    HWND windowHandle{ nullptr };
    HINSTANCE instance{ nullptr };
    U32 wwidth;
    U32 wheight;
    bool windowed;
};

}

#endif // RENDERER_DX11_DX11_CONFIG_H_