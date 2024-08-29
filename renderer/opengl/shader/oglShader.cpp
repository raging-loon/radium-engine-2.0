#include "oglShader.h"

#include <GL/glew.h>

using radium::oglShader;

void oglShader::bind()
{
    glUseProgram(m_shaderID);
}

void oglShader::unbind()
{
    glUseProgram(0);
}
