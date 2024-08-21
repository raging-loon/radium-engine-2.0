#ifndef SCENE_ECS_COMPONENT_POOL_H_
#define SCENE_ECS_COMPONENT_POOL_H_

#include <scene/ecs/sparse_set.h>
#include <core/rtl/array.h>
#include <scene/ecs/entity.h>
namespace radium
{

///
/// @brief
///     A sparsely indexed pool of types
/// 
/// @todo: look into caching
/// 
template <class CType>
class ComponentPool
{
public:

    // todo: temp code
    ComponentPool() : m_idMap{} 
    {
        m_pool.resize(32);
    }


    template<class... Args>
    CType* addComponent(entity_t eid, Args&&... args)
    {
        if (m_idMap.contains(eid))
            return getComponent(eid);
        //m_pool.push_back(CType{ rtl::forward<Args>(args)... });
        I32 pos = m_idMap.add(eid);
        m_pool[--pos] = { rtl::forward<Args>(args)... };

        return &m_pool[pos];
    }

    template <class...Args>
    CType* updateComponent(entity_t eid, Args&&... args)
    {
        I32 position = m_idMap.get_position(eid);
        if (--position < 0)
            return nullptr;
        // add destructor support if necessary
        m_pool[position] = { rtl::forward<Args>(args)... };
        return &m_pool[position];
    }

    CType* getComponent(entity_t eid)
    {
        I32 position = m_idMap.get_position(eid);
        if (--position < 0)
            return nullptr;

        printf("Found %d at index %d\n", eid, position);
        return &m_pool[position];
    }

    bool removeComponent(entity_t eid)
    {
        I32 position = m_idMap.get_position(eid);
        if (position == -1)
            return false;

        CType* targetCom = &m_pool[position];
        
        if constexpr (!std::is_trivially_destructible_v<CType>)
            targetCom->~CType();

        m_idMap.remove(eid);

        return true;

    }

private:
    sparse_set<> m_idMap;
    rtl::array<CType> m_pool;

};


}

#endif // SCENE_ECS_COMPONENT_POOL_H_