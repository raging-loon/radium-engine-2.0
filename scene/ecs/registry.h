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

    ///
    /// @brief
    ///     Create a new entity
    ///     
    ///     This will use an orphaned entity id if 
    ///     There are any available
    entity_t create();

    ///
    /// @brief
    ///     Destroy all components associated with an entity
    /// 
    ///     Will place it in the graveyard
    /// 
    void release(entity_t eid);
    
    /// @brief Does this entity exist and is not in the graveyard?
    bool isValid(entity_t t);

    /// @brief Is this entity in the graveyard?
    bool isOrphaned(entity_t t);

    size_t getEntityCount() const { return m_numEntities; }

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

    rtl::unordered_map<U64, rtl::string>
    debugGetAssociations(entity_t eid)
    {
        return m_poolFactory.getEntityComponentAssociation(eid);
    }

private:
    /// A list of IDs
    rtl::array<entity_t> m_entityIdList;

    /// A list of IDs that should be reused
    rtl::array<entity_t> m_entityGraveyard;
    
    ComponentPoolFactory m_poolFactory;

    size_t m_numEntities;

};


} // radium

#endif // SCENE_ECS_REGISTRY_H_