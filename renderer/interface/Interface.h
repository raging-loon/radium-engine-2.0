#ifndef RENDER_INTERFACE_INTERFACE_H_
#define RENDER_INTERFACE_INTERFACE_H_


#if RADIUM_API_DX11 
#   include <renderer/dx11/dx11Buffer.h>
namespace radium 
{ 
    using Buffer = radium::dx11Buffer; 
}

#elif defined(RADIUM_API_OPENGL)
#endif

#endif // RENDER_INTERFACE_INTERFACE_H_