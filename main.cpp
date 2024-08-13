#include <stdio.h>
#include "core/math/vec2.h"
#include "core/rtl/string.h"
#include "core/log/log.h"
#include "core/log/outputsystems/StdOutSystem.h"
#include "core/rtl/copy_on_write.h"
int main(int argc, char** argv)
{
    
    rtl::copy_on_write<int> test;

    test.resize(10);

    for (int i = 0; i < 10; i++)
    {
        test.at_c(i) = i * i;
    }

    radium::Logger log("test");
    log.setOutputSystem<radium::StdoutSystem>();

    log.logMemorySection(test.reference() - 8, test.get_allocation_size(), "");
    return 0;
} 

