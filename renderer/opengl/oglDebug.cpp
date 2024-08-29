#include "oglDebug.h"

#include <core/debug/globlog.h>
#include <GL/glew.h>


static const char* debugGetSource(unsigned int source);
static const char* debugGetType(unsigned int type);


void radium::oglErrorCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    int length,
    const char* message,
    const void* uParam)
{
	const char* sourceStr = debugGetSource(source);
	const char* typeStr = debugGetType(type);
	static const char* fmtstr = "[GL] Source: %s; Type: %s; Message: %s";
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:            ENGINE_CRITICAL(fmtstr, sourceStr, typeStr, message); __debugbreak(); return;
		case GL_DEBUG_SEVERITY_MEDIUM:          ENGINE_ERROR   (fmtstr, sourceStr, typeStr, message); return;
		case GL_DEBUG_SEVERITY_LOW:             ENGINE_WARNING (fmtstr, sourceStr, typeStr, message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:    ENGINE_INFO	   (fmtstr, sourceStr, typeStr, message); return;
	}
}


const char* debugGetSource(unsigned int source)
{
	switch (source)
	{
		case GL_DEBUG_SOURCE_API:               return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:   return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:       return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:       return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:             return "OTHER";
	}
	return "UNKNOWN";
}

const char* debugGetType(unsigned int type)
{
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               return "Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behavior";
		case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
		case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
		case GL_DEBUG_TYPE_MARKER:              return "Marker";
		case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
		case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
		case GL_DEBUG_TYPE_OTHER:               return "Other";
	}
	return "Unknown";
}

