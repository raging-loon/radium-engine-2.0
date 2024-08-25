#ifndef RENDERER_DX11_DX11_BUFFER_H_
#define RENDERER_DX11_DX11_BUFFER_H_

#include <renderer/dx11/dx11Common.h>
#include <renderer/interface/Buffer.h>
#include <d3d11.h>


namespace radium
{

///
/// @brief
///     Class to manage a D3D11 Buffer
/// 
class dx11Buffer
{
public:
    

private:
    ComPtr<ID3D11Buffer> m_buffer;
    BufferDescription m_description;


};


} // radium


#endif // RENDERER_DX11_DX11_BUFFER_H_