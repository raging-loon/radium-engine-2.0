#ifndef RESMGR_TYPES_IMAGE_H_
#define RESMGR_TYPES_IMAGE_H_

#include <resmgr/Resource.h>
#include <core/types.h>
namespace radium
{

class Image : public Resource
{
public:
    Image();

    RsStatus load(const byte* data, U32 size) override;
    
    I32 getHeight() const { return m_height; }
    I32 getWidth() const { return m_width;  }
    I32 getNumChannels() const { return m_channelCount;  }


private:
    const byte* m_imageData;
    
    I32 m_height;
    I32 m_width;
    I32 m_channelCount;

};

} // radium

#endif // RESMGR_TYPES_IMAGE_H_