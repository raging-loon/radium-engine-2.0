#ifndef RENDERER_OPENGL_OGL_BUFFER_H_
#define RENDERER_OPENGL_OGL_BUFFER_H_

#include <GL/glew.h>
#include <renderer/interface/Buffer.h>
#ifndef CORE_TYPES_H_
#include <core/types.h>
#endif // CORE_TYPES_H_
namespace radium
{

///
/// @brief
///     Generic OpenGL buffer
/// 
///     To create: RenderDevice.createBuffer(BufferDescription)
/// 
///     
class oglBuffer
{
public:

    oglBuffer(BufferDescription& desc, GLuint id, GLenum target);

    ~oglBuffer();

    void destroy();

    void bind();
    void bindRange(U32 index);
    
    void unbind();

    BufferType getType() const { return m_type; }
    
    void copyData(U32 size, void* data);
    void copySubData(U32 size, void* data, U32 offset);

private:
    
    /// The kind of buffer this is (e.g. VERTEX/UNIFORM)
    GLenum m_target;

    /// buffer id
    GLuint m_id;

    /// Friendlier, api agnostic type
    BufferType m_type;

    U32 m_size;

    GLuint m_uboBinding;


};


} // radium

#endif // RENDERER_OPENGL_OGL_BUFFER_H_