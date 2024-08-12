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
int main(int argc, char** argv)
{
    radium::Logger l("hello");
    l.setOutputSystem<radium::FileOutputSystem>("hello.log", 10);
    l.info("hello");

    return 0;
} 

