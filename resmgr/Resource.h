#ifndef RESMGR_RESOURCE_H_
#define RESMGR_RESOURCE_H_

#include <core/types.h>
#include "ResourceError.h"
namespace radium
{

using RID = ResourceID;

struct ResourceID
{
    U8 pakID;
    U8 index;
    U8 type;
    U8 depPoolId;
    U32 name;
};


class Resource
{
public:
    
    virtual RsStatus load(const unsigned char* data, U32 size) = 0;

};

} // radium


#endif //RESMGR_RESOURCE_H_