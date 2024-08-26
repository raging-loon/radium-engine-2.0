#ifndef RENDERER_DX11_DX11_DEVICE_H_
#define RENDERER_DX11_DX11_DEVICE_H_

#include <d3d11.h>
#include <dxgi.h>
#include <core/types.h>

#include <core/error.h>
#include <renderer/dx11/dx11Common.h>
#include <renderer/dx11/dx11Config.h>

#include <renderer/interface/DisplayInfo.h>
#include <renderer/interface/Interface.h>
#include <renderer/interface/ShaderProgram.h>
namespace radium    
{
///
///
class dx11Device
{
public:

    Status init(DisplayInfo& cfg);
    Status terminate();

    // @todo: might need to use a pool allocator for buffers etc for locality
    Buffer* createBuffer(BufferDescription bufferDesc);
    Shader* createShader(ShaderDescription shaderDesc);
private:

    bool createSwapChain();
    void createRenderTargetView();
    void createDepthStencilBuffer();
    void setViewport();

    void createGlobalVertexLayout();


    ComPtr<IDXGIFactory> createDXGIFactory(); 



private:
    U32 m_msaaQuality;
    
    /// Internal DirectX 12 Device
    ComPtr<ID3D11Device>            m_device;
    ComPtr<ID3D11DeviceContext>     m_devCtx;
    ComPtr<IDXGIFactory>            m_mainDXGIFactory;
    ComPtr<IDXGISwapChain>          m_swapChain;
    ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
    ComPtr<ID3D11Texture2D>         m_depthStencilBuffer;
    ComPtr<ID3D11InputLayout>       m_inputLayout;

    D3D11_VIEWPORT                  m_viewPort;
#ifdef _DEBUG
    /// Prints debug info to the console
    ComPtr<ID3D11Debug> m_dbgController;
#endif // _DEBUG
    DisplayInfo* m_cfg;



};
 
}



#endif // RENDERER_DX11_DX11_DEVICE_H_