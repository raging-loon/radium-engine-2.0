#include <stdio.h>
#include "core/rtl/string.h"
#include "core/log/log.h"
#include "core/log/outputsystems/StdOutSystem.h"
#include "core/log/outputsystems/FileOutputSystem.h"
#include "core/rtl/copy_on_write.h"
#include "core/rtl/hash.h"
#include "core/rtl/hash_map.h"

#include "core/rtl/iterator.h"
#include <glm/vec2.hpp>

#include "core/io/file.h"

using namespace radium;

int main(int argc, char** argv)
{
    Logger info("debug-info");
    info.setOutputSystem<StdoutSystem>();

    File f;
    
    if (f.open("test.log", File::APPEND) != Status::OK)
    {
        printf("fail\n");
    
    }

    printf("%zd\n", f.getSize());

    f.write((void*)"hello world", 10);
    f.write((void*)"hello world", 10);
    f.write((void*)"hello world", 10);
}



