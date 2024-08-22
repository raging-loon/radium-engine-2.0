#ifndef RENDERER_INTERFACE_RENDER_DEVICE_H_
#define RENDERER_INTERFACE_RENDER_DEVICE_H_


#ifdef RADIUM_API_DX12
#include <renderer/dx12/dx12Device.h>
#include <renderer/dx12/dx12Config.h>

namespace radium { using RenderDevice = radium::dx12Device; }

#endif

#endif // RENDERER_INTERFACE_RENDER_DEVICE_H_