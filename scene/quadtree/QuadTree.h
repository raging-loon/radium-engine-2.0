#ifndef SCENE_QUAD_TREE_QUAD_TREE_H_
#define SCENE_QUAD_TREE_QUAD_TREE_H_

#include <scene/ecs/entity.h>
#include <core/rtl/array.h>
#include <scene/component/Box2D.h>

namespace radium
{

constexpr I32 MAX_ENTITIES = 2;
constexpr I32 EMPTY_QNODE = -1;


struct qnode
{
    entity_t id = EMPTY_QNODE;
    glm::vec2* location;

    qnode& operator=(const qnode& other)
    {
        id = other.id;
        location = other.location;

        return *this;
    }
};


class quadtree
{
public:
    
    using QTreePool = rtl::array<quadtree>;

    quadtree(Box2D area, QTreePool* parentPool = nullptr);
    
    void insert(qnode node);
    void remove(qnode node);



private:
    void split(const qnode& node);
    void moveNodesToChildren();

private:
    Box2D m_area;
    QTreePool* m_pool;

    I8 m_numEntities = 0;
    qnode m_entities[MAX_ENTITIES];

    I32 m_children[2][2]
    {
        EMPTY_QNODE,
        EMPTY_QNODE,
        EMPTY_QNODE,
        EMPTY_QNODE
    };
};

///
/// Resources:
///     https://graphics.stanford.edu/courses/cs468-06-fall/Slides/steve.pdf
///     https://lisyarus.github.io/blog/posts/building-a-quadtree.html
///     https://www.jordansavant.com/book/algorithms/quadtree.md
/// 
/// 

} // radium

#endif // SCENE_QUAD_TREE_QUAD_TREE_H_