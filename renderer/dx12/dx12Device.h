#ifndef RENDERER_DX12_DX12_DEVICE_H_
#define RENDERER_DX12_DX12_DEVICE_H_

#include <d3d12.h>
#include <dxgi.h>

#include <core/error.h>
#include <renderer/dx12/dx12Common.h>

namespace radium    
{
///
///
class dx12Device
{
public:

    Status init();
    Status terminate();



private:
    ComPtr<ID3D12Device> m_device;

#ifdef _DEBUG
    ComPtr<ID3D12Debug> m_dbgController;
#endif // _DEBUG


};

}



#endif // RENDERER_DX12_DX12_DEVICE_H_