#include <stdio.h>
#include "core/rtl/basic_string.h"
#include "core/log/log.h"
#include "core/debug/globlog.h"
#include "core/debug/seh.h"
#include "core/rtl/smart_ptr.h"
#include <core/rtl/function.h>
#include "core/thread/thread.h"
#include <core/rtl/array.h>
#include <type_traits>
#include <core/thread/mutex.h>

using namespace radium;

rtl::string teststr = "hello";
radium::Mutex mtx;

int  threaded_add(int a, int b=1)
{
    return a + b;
}

void mutex_test()
{
    mtx.lock();
    printf("I am being accessed by tid %zd!\n", radium::thread::getThreadID());
    teststr += "!";
    mtx.unlock();

}

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    GlobLoggers::getEngineLogger()->info("hello from engine logger");
    GlobLoggers::getClientLogger()->info("hello from client logger");
    mtx.create();
    printf("%s\n", teststr.c_str());
    rtl::array<radium::thread*> threadpool;

    for (int i = 0; i < 10; i++)
    {
        threadpool.push_back(new radium::thread(mutex_test));
    }

    for (int i = 0; i < 10; i++)
    {
        threadpool[i]->join();
    }

    printf("%s\n",teststr.c_str());
}
  



