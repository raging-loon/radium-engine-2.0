#ifndef RENDERER_DX12_DX12_CONFIG_H_
#define RENDERER_DX12_DX12_CONFIG_H_

#include <windows.h>

namespace radium
{

struct RenderDeviceInitCfg
{
    HWND windowHandle{ nullptr };
    HINSTANCE instance{ nullptr };
};

}

#endif // RENDERER_DX12_DX12_CONFIG_H_