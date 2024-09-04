#include "oglBufferFactory.h"

using radium::oglBuffer;
using radium::oglBufferFactory;

static GLenum descType2GLenum[3] =
{
    GL_ARRAY_BUFFER, // BUFFER_TYPE_VERTEX
    GL_ELEMENT_ARRAY_BUFFER, // BUFFER_TYPE_INDEX,
    GL_UNIFORM_BUFFER, // BUFFER_TYPE_UNIFORM/CONSTANT
};

oglBufferFactory::oglBufferFactory()
{
 
}

rtl::shared_ptr<oglBuffer> oglBufferFactory::createBuffer(BufferDescription& desc)
{
    assert(desc.type <= 3);

    GLuint id = GL_INVALID_VALUE;
    GLenum target = descType2GLenum[(int)desc.type];

    glGenBuffers(1, &id);
    glBindBuffer(target, id);

    if (target == GL_UNIFORM_BUFFER)
    {
        // resize the buffer
        glBufferData(GL_UNIFORM_BUFFER, desc.size * desc.count, nullptr, GL_STATIC_DRAW);
        // tie it to a certain binding number (e.g. SCENE_DATA)
        glBindBufferBase(GL_UNIFORM_BUFFER, desc.binding, id);
    }

    auto buffer = rtl::make_shared<oglBuffer>(desc, id, target);

    if (desc.data)
        buffer->copyData(desc.count * desc.size, desc.data);
    buffer->unbind();

    return buffer;

}

void oglBufferFactory::init()
{
}

