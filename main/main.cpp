#include <stdio.h>
#include "core/rtl/string.h"
#include "core/log/log.h"
#include "core/debug/globlog.h"
#include "core/debug/seh.h"
#include "core/rtl/smart_ptr.h"

using namespace radium;

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    GlobLoggers::getEngineLogger()->info("hello from engine logger");
    GlobLoggers::getClientLogger()->info("hello from client logger");


}



