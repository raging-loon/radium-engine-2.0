#include "oglShader.h"


using radium::oglShader;

void oglShader::bind()
{
    glBindVertexArray(m_vao);
    glUseProgram(m_shaderID);
}

void oglShader::unbind()
{

    glUseProgram(0);
    glBindVertexArray(0);
}
