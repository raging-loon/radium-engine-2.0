#include <stdio.h>
#include "core/rtl/basic_string.h"
#include "core/log/log.h"
#include "core/debug/globlog.h"
#include "core/debug/seh.h"
#include "core/rtl/smart_ptr.h"
#include <core/rtl/function2.h>
#include "core/thread/thread.h"

#include <type_traits>
using namespace radium;

int __stdcall threaded_add(int a, int b=1)
{
    printf("I am a threading function; %d + %d = %d", a, b, a + b);
    return a + b;
}


template<class T>
struct isclass 
{
    static bool t(T* t)
    {
        if constexpr (std::is_class_v<T>)
            return true;
        return false;
    }
};

int main(int argc, char** argv)
{
    radium::setSEHHandlers();

    GlobLoggers::init();
    GlobLoggers::getEngineLogger()->info("hello from engine logger");
    GlobLoggers::getClientLogger()->info("hello from client logger");

    radium::thread test(threaded_add, 1, 2);
}  



