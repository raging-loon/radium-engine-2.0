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


class registry
{
public:

    entity_t create();

    void release(entity_t eid);
    bool isValid(entity_t t);
    bool isOrphaned(entity_t t);

    template <class T, class...Args>
    void emplace(entity_t, Args&&...args)
    {

    }

    
private:
    rtl::array<entity_t> m_entityIdList;
    rtl::array<entity_t> m_entityGraveyard;
    ComponentPoolFactory m_poolFactory;


    size_t m_numEntities;

};


} // radium

#endif // SCENE_ECS_REGISTRY_H_