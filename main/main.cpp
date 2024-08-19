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
#include <core/log/outputsystems/FileOutputSystem.h>

using namespace radium;



Logger test("test");

void test_log()
{
    test.info("hello fro mthread %ld", radium::thread::getThreadID());
}

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    ENGINE_INFO("hello");

    test.setOutputSystem<FileOutputSystem>("thread-test.log", 10);

    rtl::array<thread*> t;

    for (int i = 0; i < 10; i++)
        t.push_back(new thread(test_log));
    for (int i = 0; i < 10; i++)
        t[i]->join();

}
  



