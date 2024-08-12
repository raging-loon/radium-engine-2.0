#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/string.h"
#include "core/memory/Memory.h"
#include "core/rtl/smart_ptr.h" 
#include "core/rtl/function.h"
#include "core/rtl/array.h"
#include "core/error.h"
#include "core/log/log.h"
int main(int argc, char** argv)
{
    radium::Logger l("hello");
    l.log(radium::LogLevel::INFO, "hello");
    rtl::string test;
    test.resize(10);
    test += "hello";
    printf("\n%s\n",test.c_str());
    return 0;
} 

