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

    rtl::copy_on_write<int> x;

    rtl::copy_on_write<int> y;
    x.resize(10);

    y = x;
    y.resize(20);

    if (y.reference() == x.reference())
    {
        printf("true\n");
    }

    return 0;
} 

 