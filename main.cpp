#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/string.h"
#include "core/memory/Memory.h"
#include "core/rtl/smart_ptr.h"
#include "core/rtl/function.h"
#include "core/rtl/array.h"
#include "core/error.h"

int main(int argc, char** argv)
{
    rtl::string test = "hello";

    rtl::string t = test.substr(1,3);

    printf("%s\n",t.c_str());
    return 0;
} 

