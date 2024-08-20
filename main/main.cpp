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
using namespace radium;

struct test
{
    int x; 
    int y;
    rtl::string me;
    test(int _x, int _y) : x(_x), y(_y) 
    {
        static int num = 0;
        me = "hello";
        char t[2] = { '0' + num++, 0 };
        me += t;
    }

    int add() { return x + y; }

    test& operator=(const test& other)
    {
        x = other.x;
        y = other.y;
        me = other.me;
        return *this;
    }
    
    test(const test& other)
        : x(other.x), y(other.y), me(other.me)
    {

    }

    test& operator=(const test&& other)
    {
        x = rtl::move(other.x);
        y = rtl::move(other.y);
        me = rtl::move(other.me);
        return *this;
    }
    ~test()
    {
    }

};

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

} 
  



