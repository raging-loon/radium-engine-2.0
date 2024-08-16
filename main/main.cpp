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
#include <glm/vec2.hpp>
int main(int argc, char** argv)
{
    radium::Logger info("debug-info");
    info.setOutputSystem<radium::StdoutSystem>();
    rtl::unordered_map<int, glm::vec2> test;
    test.reserve(10);

    printf("%0x\n", rtl::hash<int>::run(0) );
    test.insert({ 1, {1.0f, 2.0f} });
    
    for (int i = 0; i < 10; i++)
    {
        test.insert({ i, {1.0f * i, 2.0f * i} });

    }

    for (const auto& i : test)
    {
        printf("%d => (%f, %f)\n",i.first, i.second.x, i.second.y);
    }
} 

