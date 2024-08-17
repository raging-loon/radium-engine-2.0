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

#include "core/debug/globlog.h"
#include "core/debug/seh.h"
using namespace radium;

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    GlobLoggers::getEngineLogger()->info("hello from engine logger");
    GlobLoggers::getClientLogger()->info("hello from client logger");


}



