#ifndef SYSTEM_CORE_PROFILER_H_
#define SYSTEM_CORE_PROFILER_H_

#include <core/rtl/string.h>
#include <core/rtl/hash_map.h>
#include <core/types.h>
#include <core/rtl/array.h>

#include <core/system/timer.h>

namespace radium
{
///
/// @brief
///     Function Profile Object
///     Used by ProfilerManager to generate output
/// 
struct FunctionProfile
{

    
    /// The number of times it was called
    U32 numTimesCalled{ 0 };

    /// A list of the time it took to execute each time it was called
    rtl::array<double> profileTimes{};
};


/// Function Name => Function Profile map
using ProfilerFunctionMap = rtl::unordered_map<rtl::string, FunctionProfile>;


///
/// @brief
///     Manages function profiles
/// 
///     A function profile consists of a name, the number of times it was called
///     and a list of execution times
/// 
///     ProfileManagers provides a way to add and modify profiles, as well as generate
///     CSV output
/// 
///     Output is generated during destruction
/// 
class ProfilerManager
{

public:

    /// Add a profile + time
    void addProfile(const rtl::string& name, double time);

    /// Write these profiles to the disk
    void dumpProfile();
    
public:
    /// singleton boilerplate

    static ProfilerManager& get()
    {
        static ProfilerManager s_instance;
        return s_instance;
    }

    ProfilerManager(const ProfilerManager& o) = delete;
    ProfilerManager& operator=(const ProfilerManager& o) = delete;

private:
    ProfilerManager() : m_profileMap{} {}
    
    ~ProfilerManager()
    {
        dumpProfile();
    }

    /// Add mm-dd-yyyy-hh-mm to the output name
    void generateFileName(rtl::string& output);

    ProfilerFunctionMap m_profileMap;

    double getAverage(const rtl::array<double>& list);

};

///
/// @brief
///     Automate profiling
/// 
///     Use @ref PROFILED_FUNCTION to create an auto profiler at the
///     beginning of your function
/// 
///     When your function is finished executing, auto profiler will go out 
///     of scope, thus destroying itself.
/// 
///     During destruction, it will register your function's name/execution time
///     with the global profiler manager
/// 
class AutoProfiler
{
public:
    AutoProfiler(const char* name);
    ~AutoProfiler();
private:
    rtl::string m_name;
    Timer m_timer;
};

}


#define PROFILED_FUNCTION(x) radium::AutoProfiler __radium_function_profiler__(x);


#endif // SYSTEM_CORE_PROFILER_H_