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
    rtl::unordered_map<rtl::string, rtl::string> test;

    test.insert({ "name", "bob" });

    for (const auto& i : test)
        printf("%s => %s\n",i.first.c_str(), i.second.c_str());
    return 0;
} 

