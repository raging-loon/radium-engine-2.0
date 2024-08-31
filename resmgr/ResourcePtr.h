#ifndef RESMGR_RESOURCE_PTR_H_
#define RESMGR_RESOURCE_PTR_H_

#ifndef RES_MGR_RESOURCE_MANAGER_H_
# include "ResourceManager.h"
#endif // RES_MGR_RESOURCE_MANAGER_H_

namespace radium
{

class Resource;

///
/// @brief
///     Ref-counted resource container
/// 
///     Essentially this is a fancy shared_ptr
///     That sends signals to the 
template <class T>
class ResourcePtr
{
    static_assert(std::is_base_of_v<Resource, T>, "T must derive from radium::Resource");

public:

    ResourcePtr()
    {

    }

    ~ResourcePtr()
    {
        
    }


private:
    struct __int_refc_container
    {
        T resource;
        U32 refCount;
    };
    RID m_rid;
    __int_ref_container m_resource;
};

} // radium


#endif // RESMGR_RESOURCE_PTR_H_