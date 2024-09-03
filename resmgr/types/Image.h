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
    
    U32 getHeight() const { return m_height; }
    U32 getWidth() const { return m_width;  }
    U32 getNumChannels() const { return m_channelCount;  }

    const byte* getImageData() const { return m_imageData; }

    ~Image() override;
private:
    byte* m_imageData;
    U32 m_height;
    U32 m_width;
    U32 m_channelCount;

};

} // radium

#endif // RESMGR_TYPES_IMAGE_H_