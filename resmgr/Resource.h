#ifndef RESMGR_RESOURCE_H_
#define RESMGR_RESOURCE_H_

#include <core/types.h>
#include "ResourceError.h"
namespace radium
{

constexpr U8 RID_PID_FILE_IS_ON_DISK = 0xff;

struct ResourceID
{
    // what resource pack this came from
    U8 pakID;
    U32 name{ 0xff };
};

using RID = ResourceID; 


class Resource
{
public:
    
    virtual RsStatus load(const byte* data, U32 size) = 0;

    void setRID(RID id) 
    {
        if (m_rid.name == 0xff)
            m_rid = id;
    }

    virtual ~Resource();
private:

    RID m_rid{};
};

} // radium


#endif //RESMGR_RESOURCE_H_