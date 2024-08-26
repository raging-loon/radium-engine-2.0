#include "dx11ShaderFactory.h"

#include <core/debug/globlog.h>
#include <d3dcompiler.h>

using namespace radium;
const char dx11ShaderFactory::s_shaderVersionList[6][7] = 
{
    "vs_5_0", "ps_5_0", "ds_5_0",
    "hs_5_0", "gs_5_0", "cs_5_0"
};



Status dx11ShaderFactory::compileShader(const rtl::string& source, const char* entryPoint, ShaderType type, ID3DBlob* shaderOut)
{
    assert(type <= 5);

    ID3DBlob* errMsg = nullptr;

    HRESULT hr = S_OK;
    hr = D3DCompile(
        source.c_str(),
        source.length(),
        nullptr,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entryPoint,
        s_shaderVersionList[type],
        0,
        0,
        &shaderOut, &errMsg
    );
    
    if (FAILED(hr))
    {
        if (errMsg)
        {
            ENGINE_ERROR("[DX11] Failed to compile shader: %s", (char*)errMsg->GetBufferPointer());
        }
        else
        {
            ENGINE_ERROR("[DX11] Failed to compile shader: 0x%0x", HRESULT_FROM_WIN32(hr));
        }

        return ERR_INVALID_PARAMETER;
    }

    return OK;
}
