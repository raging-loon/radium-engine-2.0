#ifndef RENDERER_COMMON_LAYOUT_H_
#define RENDERER_COMMON_LAYOUT_H_

#include <core/types.h>

namespace radium
{


///
/// @brief
///     Common layout descriptor - describes the layout need by a shader
/// 
struct Layout
{
    /// number of "it". e.g. 3 floats
    U32 size;
    /// offset from the start
    U32 offset;
    /// how many bytes to the next 
    U32 stride;
};

} // radium


#endif // RENDERER_COMMON_LAYOUT_H_