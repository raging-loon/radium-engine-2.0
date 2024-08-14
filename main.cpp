#include <stdio.h>
#include "core/math/vec2.h"
#include "core/rtl/string.h"
#include "core/log/log.h"
#include "core/log/outputsystems/StdOutSystem.h"
#include "core/rtl/copy_on_write.h"
#include "core/rtl/hash.h"
#include "core/rtl/hash_map.h"
int main(int argc, char** argv)
{
    radium::Logger info("debug-info");
    info.setOutputSystem<radium::StdoutSystem>();

    rtl::hash_map<int, rtl::string> test;



    for (int i = 0; i < 10; i++)
    {
        test.insert({ i, i % 2 == 0 ? "even" : "odd"});
    }

    info.logMemorySection(test.m_data.reference() - 8, test.m_data.get_allocation_size(), "");

    for (int i = 0; i < 10; i++)
    {
        printf("%d|%d => %s\n",i, test.m_data.at_p(i)->displacement, test.at(i)->c_str());
    }


    return 0;
} 

