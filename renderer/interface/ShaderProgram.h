#ifndef RENDERER_INTERFACE_SHADER_PROGRAM_H_
#define RENDERER_INTERFACE_SHADER_PROGRAM_H_

#if RADIUM_API_DX11 
#   include <renderer/dx11/dx11Shader.h>
namespace radium { using Shader = radium::dx11Shader; }
#endif

namespace radium
{

struct ShaderDescription
{
    const char* vtxSource;
    const char* psSource;
    const char* vtxEntryPoint;
    const char* psEntryPoint;

    bool isInFile;
};

} // radium



#endif // RENDERER_INTERFACE_SHADER_PROGRAM_H_