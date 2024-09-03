#ifndef RENDERER_OPENGL_OGL_TEXTURE_H_
#define RENDERER_OPENGL_OGL_TEXTURE_H_

#include <renderer/interface/Texture.h>
#include <GL/glew.h>
namespace radium
{

class oglTexture
{
public:

    oglTexture(GLuint id) : m_texId(id) {}

    void activate();

private:
    GLuint m_texId;
};

}


#endif // RENDERER_OPENGL_OGL_TEXTURE_H_