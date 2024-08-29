#ifndef RENDERER_INTERFACE_BUFFER_H_
#define RENDERER_INTERFACE_BUFFER_H_

#include <core/types.h>

namespace radium
{

enum BufferType
{
    BUFFER_TYPE_VERTEX,
    BUFFER_TYPE_INDEX,
    BUFFER_TYPE_CONSTANT,
    BUFFER_TYPE_UNIFORM = BUFFER_TYPE_CONSTANT,
    BUFFER_TYPE_TYPELESS,
    BUFFER_TYPE_NONE,
};

struct BufferDescription
{
    BufferType type;
    
    /// size of 1 object
    size_t size;
    /// number of objects
    size_t count;
    /// CB/UB binding
    U32 binding;

    void* data{ nullptr };
};


} // radium

#endif // RENDERER_INTERFACE_BUFFER_H_