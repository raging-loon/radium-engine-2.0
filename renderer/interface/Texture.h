#ifndef RENDERER_INTERFACE_TEXTURE_H_
#define RENDERER_INTERFACE_TEXTURE_H_

#include <core/types.h>

namespace radium
{

constexpr U32 TEXTURE_SAMPLER_REPEAT = 01;
constexpr U32 TEXTURE_SAMPLER_MIRROR = 02;
constexpr U32 TEXTURE_SAMPLER_CLAMP = 03;

struct TextureDescription
{
    const void* data;
    U32 height;
    U32 width;
    U32 channels;
    U32 sampleState = TEXTURE_SAMPLER_REPEAT;

};

};

#if RADIUM_API_OPENGL && !defined(RENDERER_OPENGL_OGL_TEXTURE_H_)
# include <renderer/opengl/oglTexture.h>
namespace radium { using Texture = oglTexture; }
#endif // RADIUM_API_OPENGL

#endif // RENDERER_INTERFACE_TEXTURE_H_