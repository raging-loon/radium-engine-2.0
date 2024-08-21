#ifndef SCENE_ECS_COMPONENT_POOL_FACTORY_H_
#define SCENE_ECS_COMPONENT_POOL_FACTORY_H_

#include <typeindex>

#include <core/rtl/hash_map.h>
#include <scene/ecs/componentPool.h>

#include <core/debug/globlog.h>
#include <core/rtl/smart_ptr.h>

#include <core/rtl/function.h>

namespace radium
{


///
/// @brief
///     Holds a ptr to a ComponentPool + a lambda to delete it
struct ComponentPoolContainer
{
    void* compool;
    void(*deleter)(void*);

    ComponentPoolContainer() : compool(nullptr), deleter(nullptr) { }
    
    ComponentPoolContainer(const ComponentPoolContainer& o)
    {
        compool = o.compool;
        deleter = o.deleter;
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
            delete static_cast<T*>(cpcptr);
        };
        
        m_cpools.insert({
            tid, cpc
        });
        
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


private:
     
    rtl::unordered_map<
        U64, 
        ComponentPoolContainer
    > m_cpools;


};


} // radium


#endif // SCENE_ECS_COMPONENT_POOL_FACTORY_H_