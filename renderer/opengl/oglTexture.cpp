#include "oglTexture.h"

#include <GL/glew.h>

void radium::oglTexture::activate()
{
    glBindTexture(GL_TEXTURE_2D, m_texId);
}
