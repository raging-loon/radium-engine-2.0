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
///     This works in conjunction with a ResPtr
///     The ResPtr will send a signal when a new reference is created
///     or when it gets destroyed.
///     
///     When a new reference is created, the Resource Manager will increment the 
///     associated resource's reference counter and vice versa during destruction
/// 
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
    template <class T >
    rtl::shared_ptr<T> loadResource(const rtl::string& str)
    {
        PROFILED_FUNCTION("load resource");
        static_assert(std::is_base_of_v<Resource, T>, "T must inherit from radium::Resource");

        RID id = createResourceID(str);
        id.pakID = RID_PID_FILE_IS_ON_DISK;
        auto iter = m_ridPtrMap.find(id);
        if (iter != m_ridPtrMap.end()) {
            return iter->second.static_pointer_cast<T>();
        }
        byte* resData = nullptr;
        U32 resSize = 0;
        Status loadStatus = loadResourceFromDisk(str, &resData, &resSize);

        if (loadStatus != OK)
            return rtl::shared_ptr<T>();

        rtl::shared_ptr<T> resPtr = rtl::make_shared<T>();
        if (resPtr->load(resData, resSize) != RsStatus::RES_OK)
        {
            resPtr.release();
            return rtl::shared_ptr<T>();
        }


        resPtr->setRID(id);

        m_ridDataMap.insert({ id, resData });

        m_ridPtrMap.insert({ id, resPtr });

        return resPtr;
    }

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


#endif // RES_MGR_RESOURCE_MANAGER_H_