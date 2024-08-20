#ifndef SCENE_ECS_COMPONENT_POOL_H_
#define SCENE_ECS_COMPONENT_POOL_H_

#include <scene/ecs/sparse_set.h>
#include <core/rtl/array.h>
#include <scene/ecs/entity.h>
namespace radium
{

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
        m_pool.push_back(CType{ rtl::forward<Args>(args)... });
        m_idMap.add(eid);
        return &m_pool.back();
    }

    template <class...Args>
    void updateComponent(entity_t eid, Args&&... args)
    {
        I32 position = m_idMap.get_position(eid);
        if (position == -1)
            return;
        // add destructor support if necessary
        
        m_pool[position] = { rtl::forward<Args>(args)... };

    }

    CType* getComponent(entity_t eid)
    {
        I32 position = m_idMap.get_position(eid);
        if (position == -1)
            return nullptr;
        //printf("Found %d at index %d\n", eid, position);
        return &m_pool[position];
    }

private:
    sparse_set<> m_idMap;
    rtl::array<CType> m_pool;

};


}

#endif // SCENE_ECS_COMPONENT_POOL_H_