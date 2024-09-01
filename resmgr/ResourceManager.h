#ifndef RES_MGR_RESOURCE_MANAGER_H_
#define RES_MGR_RESOURCE_MANAGER_H_

#include <core/error.h>
#include <type_traits>
#include <resmgr/Resource.h>
#include <core/rtl/string.h>
#include <core/rtl/hash_map.h>
#include <core/rtl/smart_ptr.h>
#include <core/rtl/string.h>
#include <core/system/profiler.h>
namespace radium
{
///
/// @brief 
///     Manage various game resources 
/// 
///     This maintains a list of Resource IDs (RID), Reference Counts, and 
///     an array of raw resource data to be used by various resources 
///     (e.g. PNG data for a radium::Image)
///
///     All resources MUST be derived from a radium::Resource.
/// 
///     RIDs, data pointers, and resource pointers (shared_ptr) are stored in a table:
/// 
/// @code
///     ┌───────┬──────────────┬─────────────────────┐
///     |       | m_ridDataMap |     m_ridPtrMap     |
///     ├───────┼──────────────┼─────────────────────┤
///     |  RID  |   Data Ptr   | Shared Resource Ptr |
///     └───────┴──────────────┴─────────────────────┘
/// @endcode
/// 
class ResourceManager
{
public:
    static ResourceManager& get()
    {
        static ResourceManager s_instance;
        return s_instance;
    }
    ///
    /// @brief
    ///     Initialize the resource manager
    /// @returns 
    ///     OK on success
    /// 
    Status init();

    ///
    /// @brief
    ///     Terminate the resource manager
    ///     
    ///     This will free any and all resources
    /// 
    void terminate();

    ///
    /// @brief
    ///     Load a resource of type T
    ///     
    ///     Note that T must derive from radium::Resource,
    ///     otherwise you will get a compile-time error
    /// 
    ///     defined in ResourceManager.inl
    template <class T >
    rtl::shared_ptr<T> loadResource(const rtl::string& str);

    bool isValidResource(RID rid);
    void releaseResource(RID rid);

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    Status loadResourceFromDisk(const rtl::string& location, byte** out, U32* outSize);

    RID createResourceID(const rtl::string& name);

private:

    rtl::unordered_map<RID, byte*> m_ridDataMap;
    rtl::unordered_map<RID, rtl::shared_ptr<Resource> > m_ridPtrMap;
private:
    ResourceManager() : m_ridDataMap{}, m_ridPtrMap{}
    {
    }
};

/// Prettier-looking  and faster to type alias
using ResMgr = ResourceManager;

} // radium

#include "ResourceManager.inl"
#endif // RES_MGR_RESOURCE_MANAGER_H_