#ifndef RENDERER_OPENGL_SHADER_OGL_SHADER_H_
#define RENDERER_OPENGL_SHADER_OGL_SHADER_H_

#include <core/types.h>

namespace radium
{

///
/// @brief
///     Holds a shader ID
/// 
class oglShader
{
public:
    oglShader(U32 shaderID) : m_shaderID(shaderID) {}

    void bind();
    void unbind();


private:
    U32 m_shaderID;
};

} // radium


#endif // RENDERER_OPENGL_SHADER_OGL_SHADER_H_