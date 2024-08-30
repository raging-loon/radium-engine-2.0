#ifndef RESMGR_TYPES_IMAGE_H_
#define RESMGR_TYPES_IMAGE_H_

#include <stb_image.h>
#include <resmgr/Resource.h>
namespace radium
{

class Image : public Resource
{
public:
    Image();

    RsStatus load(const unsigned char* data, U32 size) override;
    
private:
    const unsigned char* m_imageData;
    
    U32 m_height;
    U32 m_width;
    U32 m_channelCount;

};

} // radium

#endif // RESMGR_TYPES_IMAGE_H_