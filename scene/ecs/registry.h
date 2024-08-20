#ifndef SCENE_ECS_REGISTRY_H_
#define SCENE_ECS_REGISTRY_H_

#include <core/rtl/array.h>
#include <typeindex>


namespace radium
{

template <class Entity>
class registry
{
    using entity_t = Entity;
public:

private:
    rtl::array<entity_t> m_entityIdList;
    

};


} // radium

#endif // SCENE_ECS_REGISTRY_H_