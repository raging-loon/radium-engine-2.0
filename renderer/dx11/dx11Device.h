#ifndef RENDERER_DX11_DX11_DEVICE_H_
#define RENDERER_DX11_DX11_DEVICE_H_

#include <d3d11.h>
#include <dxgi.h>
#include <core/types.h>

#include <core/error.h>
#include <renderer/dx11/dx11Common.h>
#include <renderer/dx11/dx11Config.h>


namespace radium    
{
///
///
class dx11Device
{
public:

    Status init(RenderDeviceInitCfg cfg);
    Status terminate();



private:

    bool createSwapChain();

    ComPtr<IDXGIFactory> createDXGIFactory(); 

private:
    U32 m_msaaQuality;
    /// Internal DirectX 12 Device
    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_devCtx;
    ComPtr<IDXGIFactory> m_mainDXGIFactory;
    ComPtr<IDXGISwapChain> m_swapChain;

#ifdef _DEBUG
    /// Prints debug info to the console
    ComPtr<ID3D11Debug> m_dbgController;
#endif // _DEBUG
    RenderDeviceInitCfg m_cfg;



};
 
}



#endif // RENDERER_DX11_DX11_DEVICE_H_