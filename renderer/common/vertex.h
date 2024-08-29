#ifndef RENDERER_COMMON_VERTEX_H_
#define RENDERER_COMMON_VERTEX_H_

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <core/types.h>
namespace radium
{


struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};


struct VertexDescription
{
    U32 size;
    U32 offset;
    U32 stride;
};

static const VertexDescription DEFAULT_2D_VERTEX_DESC[2] =
{
    {3, 0, sizeof(Vertex)},
    {2, offsetof(Vertex, color), sizeof(Vertex)},
};


} // radium

#endif // RENDERER_COMMON_VERTEX_H_