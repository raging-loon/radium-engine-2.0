#ifndef RENDERER_OPENGL_SHADER_OGL_SHADER_H_
#define RENDERER_OPENGL_SHADER_OGL_SHADER_H_

#include <core/types.h>
#include <GL/glew.h>

namespace radium
{

///
/// @brief
///     Holds a shader ID
/// 
class oglShader
{
public:
    oglShader(U32 shaderID, GLuint vao) : m_shaderID(shaderID), m_vao(vao) {}

    void bind();
    void unbind();


private:
    U32 m_shaderID;
    GLuint m_vao;
};

} // radium


#endif // RENDERER_OPENGL_SHADER_OGL_SHADER_H_