#ifndef SCENE_ECS_REGISTRY_H_
#define SCENE_ECS_REGISTRY_H_

#include <core/rtl/array.h>
#include <typeindex>
#include <scene/ecs/entity.h>
#include <scene/ecs/ComponentPool.h>
#include <scene/ecs/ComponentPoolFactory.h>
#include <core/types.h>
namespace radium
{

///
/// @brief
///     Entity-Component Registry
/// 
///     This is heavily based off EnTT by @skypjack
/// 
///     
class registry
{
public:

    registry();
    ~registry();

    entity_t create();

    void release(entity_t eid);
    bool isValid(entity_t t);
    bool isOrphaned(entity_t t);

    ///
    /// @brief
    ///     Construct a new T in it's respecive pool
    ///     
    template <class T, class...Args>
    T*  emplace(entity_t eid, Args&&...args)
    {
        auto* pool = m_poolFactory.get<T>();
        assert(pool);
        return pool->addComponent(eid, rtl::forward<Args>(args)...);
    }

    ///
    /// @brief
    ///     Remove an entity from a component
    /// 
    template <class T>
    bool remove(entity_t eid)
    {
        auto* pool = m_poolFactory.get<T>();
        assert(pool);
        return pool->removeComponent(eid);
    }
    
    ///
    /// @brief
    ///     Update the component T for eid 
    /// 
    template <class T, class...Args>
    T* update(entity_t eid, Args&&... args)
    {
        auto* pool = m_poolFactory.get<T>();
        assert(pool);
        return pool->updateComponent(eid, rtl::forward<Args>(args)...);
    }
   
    ///
    /// @brief
    ///     Is there a pool for T that contains eid?
    /// 
    template <class T>
    bool has(entity_t eid)
    {
        auto* pool = m_poolFactory.getIfExists<T>();
        
        if (!pool) return false;

        return pool->getComponent(eid) != nullptr;
    }


    ///
    /// @brief
    ///     Are there pools for each T that contains eid?
    /// 
    template<class... Types>
    bool allof(entity_t eid)
    {
        if constexpr (sizeof...(Types) == 1)
            return has<Types...>(eid);
        else
            return (allof<Types>(eid) && ...);
    }
    ///
   /// @brief
   ///     Are there any pools for each T that contains eid?
   /// 
    template <class... Types>
    bool anyof(entity_t eid)
    {
        return (allof<Types>(eid) || ...);
    }



private:
    rtl::array<entity_t> m_entityIdList;
    rtl::array<entity_t> m_entityGraveyard;
    ComponentPoolFactory m_poolFactory;


    size_t m_numEntities;

};


} // radium

#endif // SCENE_ECS_REGISTRY_H_