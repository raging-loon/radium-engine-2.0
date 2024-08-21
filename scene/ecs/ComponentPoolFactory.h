#ifndef SCENE_ECS_COMPONENT_POOL_FACTORY_H_
#define SCENE_ECS_COMPONENT_POOL_FACTORY_H_

#include <typeindex>

#include <core/rtl/hash_map.h>
#include <scene/ecs/ComponentPool.h>

#include <core/debug/globlog.h>
#include <core/rtl/smart_ptr.h>

#include <core/rtl/function.h>

namespace radium
{


///
/// @brief
///     Holds a ptr to a ComponentPool + a lambda to delete/remove it
struct ComponentPoolContainer
{
    void* compool;
    void(*deleter)(void*);
    bool(*remover)(entity_t, void* );


    ComponentPoolContainer() : compool(nullptr), deleter(nullptr), remover(nullptr) { }
    
    ComponentPoolContainer(const ComponentPoolContainer& o)
    {
        compool = o.compool;
        deleter = o.deleter;
        remover = o.remover;
    }

};

///
/// @brief
///     Creates new component pools
///     
///     These component pools are uniquely identified by 
///     the type index the compiler gives them
/// 
///     Creating a new pool:
///     @code
///         my_poolfactory.addNewPool<MyComponent>();
///     @endcode
/// 
///     Getting a pool, this will create it if it does not exist
///     @code
///         my_poolfactory.get<MyComponent>();
///     @endcode
/// 
///     How does this handle deletions, considering ComponentPools
///     need to free memory allocated by sparse_sets et. al.?
///     
///     This is handled via a very tricky trick using lambdas.
///     Hopefully this will be refactored in the future...
/// 
///     Essentially, a new lambda is creating during compile time for 
///     each type the compiler detects. It's job is to cast a pointer to 
///     ComponentPool<T> and delete it. This is needed because once a pool
///     is stored, all associated type information is lost.
///     
///     In debug builds, this will contain a map of typeid => type names
///     Use @ref getEntityComponentAssociation to get all associateed 
///     Components for any given entity.
/// 
/// 
///     @todo: look at other alternative storage methods. 
///            rtl::array will check for copy on write every access
/// 
class ComponentPoolFactory
{
public:

    ComponentPoolFactory()
    {
    }


    ~ComponentPoolFactory()
    {
        for (auto& i : m_cpools)
        {
            i.second.deleter(i.second.compool);
        }
    }

    ///
    /// @brief
    ///     Add ComponentPool<T> to the list of pools
    ///     
    template <class T>
    ComponentPool<T>* addNewPool()
    {
        auto tid = std::type_index(typeid(T)).hash_code();
        ENGINE_INFO("Creating new ComponentPool with id 0x%0zx", tid);
        
        auto* newpool = new ComponentPool<T>();
        
        ComponentPoolContainer cpc;

        cpc.compool = static_cast<void*>(newpool),
        
        cpc.deleter = [](void* cpcptr) {
            delete static_cast<ComponentPool<T>*>(cpcptr);
        };
        
        cpc.remover = [](entity_t eid, void* ptr) {
            return static_cast<ComponentPool<T>*>(ptr)->removeComponent(eid);
        };
        m_cpools.insert({
            tid, cpc
        });
#ifdef _DEBUG
        m_debugTypeAssoc.insert({ tid,  std::type_index(typeid(T)).name() });
#endif
        return newpool;
    }

    ///
    /// @brief
    ///     Get pool storing T. The pool will be created if it does not exist
    ///     
    template<class T>
    ComponentPool<T>* get()
    {
        auto pool = m_cpools.find(std::type_index(typeid(T)).hash_code());
        if (pool == m_cpools.end())
        {
            return addNewPool<T>();
        }
        return static_cast<ComponentPool<T>*>(pool->second.compool);
    }


    ///
    /// @brief
    ///     Get pool storing T. The pool will be created if it does not exist
    ///     
    template<class T>
    ComponentPool<T>* getIfExists()
    {
        auto pool = m_cpools.find(std::type_index(typeid(T)).hash_code());
        if (pool == m_cpools.end())
        {
            return nullptr;
        }
        return static_cast<ComponentPool<T>*>(pool->second.compool);
    }

    void removeAll(entity_t eid)
    {

        for (auto& i : m_cpools)
            i.second.remover(eid, i.second.compool);
    }

    ///
    /// @brief
    ///     get a map containing the ID/typename of 
    ///     each component an entity is associated with
    /// 
    ///     In release mode, this will be empty
    ///     
    rtl::unordered_map<U64, rtl::string>
    getEntityComponentAssociation(entity_t eid)
    {
        rtl::unordered_map<U64, rtl::string> map;
#ifdef _DEBUG
        for (auto& i : m_cpools)
        {
            ComponentPool<void*>* pool = static_cast<ComponentPool<void*>*>(i.second.compool);
            if (pool->exists(eid))
            {
                map.insert({
                    i.first,
                    m_debugTypeAssoc[i.first]
                });
            }
        }
#endif // _DEBUG
        return map;
    }

private:
     
    rtl::unordered_map<
        U64, 
        ComponentPoolContainer
    > m_cpools;
#ifdef _DEBUG
    rtl::unordered_map<U64, rtl::string> m_debugTypeAssoc;
#endif

};


} // radium


#endif // SCENE_ECS_COMPONENT_POOL_FACTORY_H_