#ifndef RENDERER_INTERFACE_RENDER_DEVICE_H_
#define RENDERER_INTERFACE_RENDER_DEVICE_H_


#ifdef RADIUM_API_DX12
#include <renderer/dx12/dx12Device.h>
#include <renderer/dx12/dx12Config.h>
namespace radium { using RenderDevice = radium::dx12Device; }

#elif defined(RADIUM_API_DX11)
#include <renderer/dx11/dx11Device.h>
#include <renderer/dx11/dx11Config.h>
namespace radium { using RenderDevice = radium::dx11Device; }

#elif defined(RADIUM_API_OPENGL)
#include <renderer/opengl/oglDevice.h>
namespace radium { using RenderDevice = radium::oglDevice; }

#endif

#endif // RENDERER_INTERFACE_RENDER_DEVICE_H_