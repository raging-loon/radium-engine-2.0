#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/string.h"
#include "core/memory/Memory.h"
#include "core/rtl/smart_ptr.h"
#include "core/rtl/function.h"
#include "core/rtl/array.h"

struct asdf
{
    int x;
    int y;
    int z;
};

int main(int argc, char** argv)
{
    rtl::string test = "hello";

    test += "hello";
    test += "hello";
    test += "hello";
    test += "hello";
    test += "hello";
    test += "hello";
    test += "hello";
    test += "hello";

    printf("%s\n",test.c_str());
    return 0;
} 

