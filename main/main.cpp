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
using namespace radium;



int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");
 
    rtl::array<int> test;
    test.resize(10);
    test.fill(-1);

    int x = 1;
    int y = 2;
    printf("%d | %d\n", x, y);

    rtl::swap(x, y);
    printf("%d | %d\n", x, y);

    for (int i = 0; i <= 6; i++)
        test.push_back(i);

    printf("%d | %d\n",test.front(), test.back());
    
    printf("%d\n", test[6]);
    sparse_set test2;
    test2.add(5);
    test2.add(6);

    if (test2.contains(5))
        printf("yes\n");

    test2.remove(5);
    if (test2.contains(5))
        printf("yes\n");
    if (test2.contains(6))
        printf("yes6\n");    
    if (test2.contains(3))
        printf("yes3\n");
}
  



