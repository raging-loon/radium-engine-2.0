#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/string.h"
#include "core/memory/Memory.h"
#include "core/rtl/smart_ptr.h" 
#include "core/rtl/function.h"
#include "core/rtl/array.h"
#include "core/error.h"
#include "core/log/log.h"
#include "core/log/outputsystems/FileOutputSystem.h"
#include "core/rtl/utility.h"
int main(int argc, char** argv)
{
    rtl::string str1 = "hello";

    rtl::string test = "hello world";

    rtl::string test2 = str1 + " world";

    printf("%s\n", test2.c_str());
    printf("%s\n", str1.c_str());
    return 0;
} 

 