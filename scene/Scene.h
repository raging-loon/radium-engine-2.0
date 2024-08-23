#ifndef SCENE_SCENE_H_
#define SCENE_SCENE_H_

#include <core/rtl/array.h>
#include <core/rtl/hash_map.h>

#include <scene/ecs/registry.h>
#include <scene/ecs/entity.h>

#include <glm/vec2.hpp>

namespace radium
{

class quadtree;


class Scene
{
public:
    using EntityLocationMap = rtl::unordered_map < entity_t, glm::vec2*>;

    Scene();
    ~Scene();



private:
    registry m_registry;
    EntityLocationMap m_idLocationMap;

private:
    rtl::array<quadtree> m_treeAllocator;
    quadtree* m_treeRoot;

};


} // radium

#endif // SCENE_SCENE_H_