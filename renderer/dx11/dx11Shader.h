#ifndef RENDERER_DX11_DX11_SHADER_H_
#define RENDERER_DX11_DX11_SHADER_H_

#include <d3d11.h>
#include <d3dcompiler.h>

#include <core/error.h>

namespace radium
{


class dx11Shader
{
    ID3D11VertexShader* m_vtxShader;
    ID3D11PixelShader* m_pixelShader;
    ID3D11InputLayout* m_inputLayout;
};

} // radium

#endif // RENDERER_DX11_DX11_SHADER_H_