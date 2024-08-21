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
#include <scene/ecs/ComponentPool.h>
#include <scene/component/Sprite2D.h>
#include <typeindex>

#include <scene/ecs/ComponentPoolFactory.h>
#include <scene/ecs/registry.h>
using namespace radium; 


int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

   


} 
  



