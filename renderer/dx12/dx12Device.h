#ifndef RENDERER_DX12_DX12_DEVICE_H_
#define RENDERER_DX12_DX12_DEVICE_H_

#include <d3d12.h>
#include <dxgi.h>

#include <core/error.h>
#include <renderer/dx12/dx12Common.h>
#include <renderer/dx12/dx12Config.h>
namespace radium    
{
///
///
class dx12Device
{
public:

    Status init(RenderDeviceInitCfg cfg);
    Status terminate();



private:
    /// Internal DirectX 12 Device
    ComPtr<ID3D12Device> m_device;

#ifdef _DEBUG
    /// Prints debug info to the console
    ComPtr<ID3D12Debug> m_dbgController;
#endif // _DEBUG
    

    RenderDeviceInitCfg m_cfg;

};

}



#endif // RENDERER_DX12_DX12_DEVICE_H_