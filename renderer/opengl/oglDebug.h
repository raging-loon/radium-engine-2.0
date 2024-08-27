#ifndef RENDERER_OPENGL_OGL_DEBUG_H_
#define RENDERER_OPENGL_OGL_DEBUG_H_

namespace radium
{

void oglErrorCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    int length,
    const char* message,
    const void* uParam);

} // radium


#endif // RENDERER_OPENGL_OGL_DEBUG_H_