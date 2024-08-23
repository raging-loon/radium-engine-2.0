#include <renderer/dx11/dx11Device.h>
#include <core/error.h>
#include <core/types.h>

#include <d3d11.h>
#include <dxgi.h>

using radium::dx11Device;
using radium::Status;
using radium::RenderDeviceInitCfg;

Status dx11Device::init(RenderDeviceInitCfg cfg)
{
    assert(cfg.instance && cfg.windowHandle);
    U32 createFlags = 0;

#ifdef _DEBUG
    createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG
    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        m_device.GetAddressOf(),
        &featureLevel,
        &m_devCtx
    );

    if (FAILED(hr))
    {
        MessageBoxA(nullptr, "Failed to create DirectX11 Device. Add more dbeug info pls.", nullptr, 0);
        return ERR_INVALID_VALUE;
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBoxA(0, "Direct3D Feature Level 11 Unsupported. Try updating your drivers. (or getting a modern os...)", 0, 0);
        return ERR_INVALID_VALUE;
    }

    m_device->CheckMultisampleQualityLevels(
        DXGI_FORMAT_R8G8_B8G8_UNORM, 4, &m_msaaQuality
    );

    m_mainDXGIFactory = createDXGIFactory();

    if (!createSwapChain())
    {
        return ERR_INVALID_VALUE;
    }

    return Status();
}

Status dx11Device::terminate()
{
    return Status();
}

bool dx11Device::createSwapChain()
{
    DXGI_SWAP_CHAIN_DESC scd;
    
    scd.BufferDesc = {
        // @todo: add w/h/vsync info to rdc
        .Width =   800,
        .Height = 600,
        .RefreshRate = {60,1},
        .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
        .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
        .Scaling = DXGI_MODE_SCALING_UNSPECIFIED
    };

    if (m_msaaQuality > 0)
        scd.SampleDesc = { .Count = 4, .Quality = m_msaaQuality - 1 };
    else
        scd.SampleDesc = { .Count = 1, .Quality = 0 };

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = m_cfg.windowHandle;
    // @todo: add windowed support to config
    scd.Windowed = false;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = 0;



    return false;
}

ComPtr<IDXGIFactory> dx11Device::createDXGIFactory()
{
    IDXGIDevice* dxgiDev = nullptr;
    IDXGIAdapter* dxgiAdapter = nullptr;
    ComPtr<IDXGIFactory> dxgiFactory = nullptr;

    m_device->QueryInterface(IID_PPV_ARGS(&dxgiDev));
    dxgiDev->GetParent(IID_PPV_ARGS(&dxgiAdapter));
    dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));

    dxgiDev->Release();
    dxgiAdapter->Release();


    return dxgiFactory;

}
