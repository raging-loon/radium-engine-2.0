#include <stdio.h>
#include "core/math/vec2.h"
#include "core/rtl/string.h"
#include "core/log/log.h"
#include "core/log/outputsystems/StdOutSystem.h"
#include "core/log/outputsystems/FileOutputSystem.h"
#include "core/rtl/copy_on_write.h"
#include "core/rtl/hash.h"
#include "core/rtl/hash_map.h"

#include "core/rtl/iterator.h"

int main(int argc, char** argv)
{
    radium::Logger info("debug-info");
    info.setOutputSystem<radium::StdoutSystem>();

    rtl::hash_map<int, rtl::string> test;
    for (int i = 0; i < 10; i++)
    {
        test.insert({ i, i % 2 == 0 ? "even" : "odd" });
    }

    //rtl::generic_iterator < rtl::displaced_pair<int, rtl::string > > b(test.m_data.copy());
    //rtl::generic_iterator < rtl::displaced_pair<int, rtl::string > > e(test.m_data.copy() + test.m_data.get_num_data());

   
    for (const auto& i : test)
    {
        printf("%d\n", i.displacement);
    }
    

    return 0;
} 

