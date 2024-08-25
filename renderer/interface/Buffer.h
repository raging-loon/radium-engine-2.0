#ifndef RENDERER_INTERFACE_BUFFER_H_
#define RENDERER_INTERFACE_BUFFER_H_

#if RADIUM_API_DX11 
#   include <renderer/dx11/dx11Buffer.h>
    namespace radium { using Buffer = radium::dx11Buffer; }
#endif

#include <core/types.h>

namespace radium
{

enum BufferType
{
    BUFFER_TYPE_NONE,
    BUFFER_TYPE_TYPELESS,
    BUFFER_TYPE_VERTEX,
    BUFFER_TYPE_INDEX,
    BUFFER_TYPE_CONSTANT,
    BUFFER_TYPE_UNIFORM = BUFFER_TYPE_CONSTANT,
};

struct BufferDescription
{
    BufferType type;
    size_t size;
    size_t count;
};

} // radium

#endif // RENDERER_INTERFACE_BUFFER_H_