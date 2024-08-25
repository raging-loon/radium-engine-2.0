# Debugging and Profiling in Radium

## Intro
Debugging is very important.

## Logging

Radium has two main logging components:
1. Loggers
2. Global Loggers

### Loggers

Raduim's logger is very simple.
It's responsibility is to contruct output, e.g. adding a time/date, adding the log type, etc.

However, it is not solely responsible for writing to an output stream. This is the responsibility of an 
`OutputSystem`.  `OutputSystem`s deal with the output of the logger. The two main output systems are:

1. `StdoutSystem`: Writes logs to some standard output stream
2. `FileOutputSystem`:
    Writes output to a file. This is buffered, by default it will hold 10 logs before writing them

If you are writing a new output system, it MUST be thread safe. This is easily accomplished using the `THREAD_SAFE_CLASS`
and `THREAD_SAFE_FUNCTION` macros.

e.g.:

```C++

#include <core/thread/thread.h>
#include <core/log/outputsystems/OutputSystem.h>

class FancyNewOutputSystem : public OutputSystem
{
    THREAD_SAFE_CLASS

    ... code ...

    void myFunctionThatModifiesSomethingInSomeWayAndViolatesNamingConventions()
    {
        THREAD_SAFE_FUNCTION
        ... code ...
    }

}
```

These macros will automatically create a mutex and scoped mutex locker for you.
It is important that `THREAD_SAFE_FUNCTION` is not in the contructor, other wise there may be a deadlock

### Global Loggers

These are defined in `/core/debug/globlog.h`

There are two global loggers, one for clients, one for the engine.

These are accessible by either directly calling them(e.g. `GlobLoggers::getEngineLogger()->info`) or by using the 
macros defined: `ENGINE_<logging level>`, e.g. `ENGINE_INFO`


### Logging Memory

Loggers have the capability of hex-dumping a section of memory.
Keep in mind, there is no way to check that this section is valid.

Use `radium::Logger::logMemorySection` to log memory. E.g. `myLogger.logMemorySection(myobject, myobject + sizeof(myobject), "my message");`


## Graphics Debugging
Radium does not come with advanced graphics debugging features. This is left up to tools such as 
RenderDoc and Visual studio. 

However, there are ways to help.

### DirectX
In a debug build, our DirectX device will have the debug layer enabled, logging output to the console.

There also exists a macro `DX_CHK` to check the results of an API call. This will parse the error returned and present a much nicer error message.

## Profiling

        
1. Function Profiles 

    A profile for a function, how many times it has been called and execution times
2. A Profiler Manager: one of a very limited number of singletons

    This manages function profiles and allows client to register new execution times
    This will also write any profiles to the disk in the form of a csv file.
3. AutoProfiler
    
    This helps automate profiling. It will create a small class that keeps track
    of the current function and a timer. It will communicate execution times with the 
    profiler manager

Example:

```C++

#include <core/system/profiler.h>

void myFunction()
{
    PROFILED_FUNCTION

    ... work ...
}
```