#ifndef SCENE_ECS_REGISTRY_H_
#define SCENE_ECS_REGISTRY_H_

#include <core/rtl/array.h>
#include <typeindex>
#include <scene/ecs/entity.h>
#include <scene/ecs/componentPool.h>
#include <core/types.h>
namespace radium
{

constexpr static U64 TOTAL_NUM_VIABLE_COMPONENTS = 1;

class registry
{
public:

private:
    rtl::array<entity_t> m_entityIdList;
    
    

};


} // radium

#endif // SCENE_ECS_REGISTRY_H_