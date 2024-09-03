#ifndef RESMGR_RESOURCE_H_
#define RESMGR_RESOURCE_H_

#include <core/types.h>
#include "ResourceError.h"
#include <core/rtl/hash.h>
namespace radium
{

/// Identifies a resource
/// Used for locating its data in a map
using RID = U32; 

///
/// @brief
///     Resource base-class
/// 
///     This should be contained within a shared_ptr
///     to help manage it's lifetime. 
///     
///     Resource is responsible for managing it's own data
/// 
class Resource
{
    friend class ResourceManager;
public:
    
    virtual RsStatus load(const byte* data, U32 size) = 0;


    RID getResourceID() const { return m_rid; }
    virtual ~Resource() {};
private:

    RID m_rid{};
};

} // radium

#endif //RESMGR_RESOURCE_H_