#ifndef RESMGR_RESOURCE_H_
#define RESMGR_RESOURCE_H_

#include <core/types.h>
#include "ResourceError.h"
#include <core/rtl/hash.h>
namespace radium
{

constexpr U8 RID_PID_FILE_IS_ON_DISK = 0xff;

/// Identifies a resource
/// Used for locating its data in a map
struct ResourceID
{
    U32 name{ 0xff };
    // what resource pack this came from
    U8 pakID;
    U8 _pad1{0};
    U8 _pad2{0};
    U8 _pad3{0};

};
/// friendlier alias
using RID = ResourceID; 
bool operator==(RID l, RID r);


///
/// @brief
///     Resource base-class
/// 
///     This should be contained within a shared_ptr
///     to help manage it's lifetime. 
///     
///     When the resource is destroyed, it's destructor will
///     alert the ResourceManager that it's resource (RID)
///     is no longer in use and can be freed
/// 
class Resource
{
public:
    
    virtual RsStatus load(const byte* data, U32 size) = 0;

    void setRID(RID id)
    {
        if (m_rid.name == 0xff)
            m_rid = id;
    }
    RID getResourceID() const { return m_rid; }
    virtual ~Resource();
private:

    RID m_rid{};
};

} // radium


///
/// @brief
///     Hash function for RIDs
/// 
template <>
struct rtl::hash<radium::RID>
{
    static uint32_t run(radium::RID rid, uint32_t hash = HASH_SEED)
    {
        radium::U8* bytes = (radium::U8*)&rid;
        hash = (bytes[4] ^ hash) * HASH_PRIME;
        hash = (bytes[3] ^ hash) * HASH_PRIME;
        hash = (bytes[2] ^ hash) * HASH_PRIME;
        hash = (bytes[1] ^ hash) * HASH_PRIME;
        hash = (bytes[0] ^ hash) * HASH_PRIME;
        return hash;
    }
};

#endif //RESMGR_RESOURCE_H_