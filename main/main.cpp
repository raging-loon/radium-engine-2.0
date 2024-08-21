#include <stdio.h>
#include <core/rtl/basic_string.h>
#include <core/log/log.h>
#include <core/debug/globlog.h>
#include <core/debug/seh.h>
#include <core/rtl/smart_ptr.h>
#include <core/rtl/function.h>
#include <core/memory/PoolAllocator.h>
#include <core/rtl/array.h>

#include <scene/ecs/sparse_set.h>
#include <scene/ecs/componentPool.h>
#include <scene/component/Sprite2D.h>
#include <typeindex>

#include <scene/ecs/ComponentPoolFactory.h>
using namespace radium; 

struct test
{
    int the_int;
    int the_short;
    int the_add() { return the_int + the_short; }

    test(int x, int y) : the_int(x), the_short(y) {}

    test(const test& o) : the_int(o.the_int), the_short(o.the_short) {}

};



int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

    ComponentPoolFactory cpf;

    auto* np = cpf.addNewPool<test>();

    
    np->addComponent(1, 1, 2);


    auto* sp = cpf.addNewPool<Sprite2D>();

    sp->addComponent(1, "skamtebord");
    sp->addComponent(2, "lobster");

    cpf.get<Sprite2D>()->getComponent(1)->printName();
    cpf.get<Sprite2D>()->getComponent(2)->printName();
    printf("%d\n", cpf.get<test>()->getComponent(1)->the_add());
} 
  



