#include "oglBuffer.h"

using radium::BufferDescription;
using radium::oglBuffer;

oglBuffer::oglBuffer(BufferDescription& desc, GLuint id, GLenum target)
    : m_id(id), 
      m_target(target), 
      m_type(desc.type), 
      m_size(desc.size),
      m_uboBinding(desc.binding)
{
}

oglBuffer::~oglBuffer()
{
    destroy();
}

void oglBuffer::destroy()
{
    if (m_id != GL_INVALID_VALUE)
    {
        glDeleteBuffers(1, &m_id);
        m_id = GL_INVALID_VALUE;
    }
}

void oglBuffer::bind()
{
    glBindBuffer(m_target, m_id);
}

void oglBuffer::bindRange(U32 index)
{
    glBindBufferRange(
        m_target,
        m_uboBinding,
        m_id,
        index * m_size,
        m_size
    );
}

void oglBuffer::unbind()
{
    glBindBuffer(m_target, 0);
}

void oglBuffer::copyData(U32 size, void* data)
{
    glBufferData(
        m_target,
        size,
        data,
        GL_STATIC_DRAW
    );
}

void oglBuffer::copySubData(U32 size, void* data, U32 offset)
{
    bind();
    glBufferSubData(
        m_target,
        offset,
        size,
        data
    );
}
