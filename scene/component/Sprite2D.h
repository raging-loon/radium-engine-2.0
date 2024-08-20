#ifndef SCENE_COMPONENT_SPRITE_2D_H_
#define SCENE_COMPONENT_SPRITE_2D_H_

#include <core/rtl/string.h>

namespace radium
{

class Sprite2D
{
public:
    Sprite2D(const char* str) : m_name(str) {}
    void printName() { printf("%s\n", m_name.c_str()); }
private:
    rtl::string m_name;

};

} // radium



#endif // SCENE_COMPONENT_SPRITE_2D_H_