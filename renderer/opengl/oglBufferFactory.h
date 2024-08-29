#ifndef RENDERER_OPENGL_OGL_BUFFER_FACTORY_H_
#define RENDERER_OPENGL_OGL_BUFFER_FACTORY_H_

#include "oglBuffer.h"
#include <renderer/common/vertex.h>
#include <core/rtl/smart_ptr.h>
#include <GL/glew.h>

namespace radium
{

class oglBufferFactory
{
public:
    oglBufferFactory();
    rtl::shared_ptr<oglBuffer> createBuffer(BufferDescription& desc);

private:

    void bindLayout();

    /// vertex array object for vertex buffers
    GLuint m_vao;
    
    bool layoutSet;
};


} // radium


#endif // RENDERER_OPENGL_OGL_BUFFER_FACTORY_H_