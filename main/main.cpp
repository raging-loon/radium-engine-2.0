#include <stdio.h>
#include "core/rtl/basic_string.h"
#include "core/log/log.h"
#include "core/debug/globlog.h"
#include "core/debug/seh.h"
#include "core/rtl/smart_ptr.h"
#include <core/rtl/function.h>
#include "core/thread/thread.h"
#include <core/rtl/array.h>
#include <functional>
#include <type_traits>
using namespace radium;

int  threaded_add(int a, int b=1)
{
    GlobLoggers::getClientLogger()->info("I am a threading function; %d + %d = %d", a, b, a + b);
    return a + b;
}

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    GlobLoggers::getEngineLogger()->info("hello from engine logger");
    GlobLoggers::getClientLogger()->info("hello from client logger");

    rtl::array<radium::thread*> threads;
    threads.resize(10);
    for (int i = 0; i < 10; i++)
    {
        threads.push_back(new radium::thread(threaded_add, i, i));
    }
    for (int i = 0; i < 10; i++)
    {
        threads[i]->join();
    }
}
  



