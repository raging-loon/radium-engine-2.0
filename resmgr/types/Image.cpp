#include "Image.h"

#include <core/debug/globlog.h>

#include <stb_image.h>

using radium::Image;
using radium::RsStatus;

Image::Image() 
    : m_imageData(nullptr), m_height(-1), m_width(-1), m_channelCount(-1)
{
}


RsStatus Image::load(const byte* data, U32 size)
{

    m_imageData = stbi_load_from_memory(data, (int)size, (I32*)&m_height, (I32*)&m_width, (I32*)&m_channelCount, 0);

    if (!m_imageData)
    {
        ENGINE_ERROR("Failed to load image: %s", stbi_failure_reason());
        return RES_INVALID_DATA;
    }

    return RES_OK;
}

Image::~Image()
{
    if (m_imageData)
        stbi_image_free(m_imageData);
}
