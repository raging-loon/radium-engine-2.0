#ifndef SCENE_COMPONENT_BOX_2D_H_
#define SCENE_COMPONENT_BOX_2D_H_

#include <glm/vec2.hpp>
#include <limits.h>
namespace radium
{


struct Box2D
{
    glm::vec2 min{ FLT_MAX, FLT_MAX };
    glm::vec2 max{ FLT_MIN, FLT_MIN };

    glm::vec2 midpoint()
    {
        return { (min.x + min.y) / 2.0f, (max.x + max.y) / 2.0f, };
    }
};


} // radium

#endif // SCENE_COMPONENT_BOX_2D_H_