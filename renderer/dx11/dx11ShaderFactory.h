#ifndef RENDERER_DX11_DX11_SHADER_FACTORY_H_
#define RENDERER_DX11_DX11_SHADER_FACTORY_H_

#include <d3d11.h>
#include <core/rtl/string.h>
#include <renderer/dx11/dx11Common.h>
#include <core/error.h>
#include <renderer/dx11/dx11Shader.h>

namespace radium
{

class dx11ShaderFactory
{
public:

    enum ShaderType
    {
        VERTEX,
        PIXEL,
        DOMAIN_,
        HULL,
        GEOMETRY,
        COMPUTE
    };


    Status compileShader(const rtl::string& source, const char* entryPoint, ShaderType type, ID3DBlob* shaderOut);


private:

    static const char s_shaderVersionList[6][7];
    /*
    {
	"vs_5_0", "ps_5_0", "ds_5_0",
	"hs_5_0", "gs_5_0", "cs_5_0"
};
    */



};

} // radium

#endif // RENDERER_DX11_DX11_SHADER_FACTORY_H_