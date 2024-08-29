#ifndef RENDER_INTERFACE_INTERFACE_H_
#define RENDER_INTERFACE_INTERFACE_H_


#if RADIUM_API_DX11 
#   include <renderer/dx11/dx11Buffer.h>
#   include <renderer/dx11/dx11Shader.h>
namespace radium 
{ 
    using Buffer = radium::dx11Buffer; 
    using Shader = radium::dx11Shader; 
}

#elif defined(RADIUM_API_OPENGL)
#   include <renderer/opengl/oglBuffer.h>
#   include <renderer/opengl/shader/oglShader.h>
namespace radium
{
    using Buffer = radium::oglBuffer;
    using Shader = radium::oglShader;
}
#endif

#endif // RENDER_INTERFACE_INTERFACE_H_