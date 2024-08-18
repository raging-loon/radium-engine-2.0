#ifndef CORE_THREAD_H_
#define CORE_THREAD_H_

#include <core/types.h>
#include <core/rtl/utility.h>
#include <Windows.h> // TEMPL CODE: TODO REMOVE
#include <stdio.h>

#include <core/rtl/function.h>
namespace radium
{

///
/// @brief
///     This is what is passed to the OS create thread
///     function.
/// 
///     This expects p to be a pointer to an rtl::function
///     of type void();
/// 
///     It will extract that function p and call it.
/// 
class dummy_thread_runner
{
public:
    static void* run(void* p)
    {
        auto* fn = static_cast<rtl::function<void()>*>(p);
        (*fn)();
        return nullptr;
    }
};

///
/// @brief
///     Basic Thread class
/// 
///     This relies on the operating system's thread API
///     Specifically Window's Thread API and pthreads on *nix
///     Implementations are found in /platform/<name>/thread/thread.cpp
/// 
///     To use:
///     @code
///     radium::thread mythread(myfunction, myargs...);    
///     mythread.join(); 
///     @endcode
/// 
///     Thread supports multiple arguments by hiding them inside of a lambda 
///     stored in @dummy
/// 
///     This dummy function is what @ref dummy_thread_runner will run
///     
///     
class thread
{
public:

    
    template<class T, class ...Args>
    explicit thread(T&& t, Args&&... args)
    {
        dummy = [=]() mutable {
            rtl::forward<T>(t)(rtl::forward<Args>(args)...);
        };
        start(dummy_thread_runner::run, (void*)&dummy);
    }

    thread& operator=(thread&& other)
    {
        dummy = rtl::move(other.dummy);
        m_thread = rtl::move(other.m_thread);
        m_id = rtl::move(other.m_id);
        return *this;
    }

    /// wait for this thread to finish
    void join();

    /// The TID for *this* thread
    size_t getId() const;

    const ThreadObject getNativeThreadObject() const
    {
        return m_thread;
    }

public:
    /// get thread id for caller
    static size_t getThreadID();


private:
    /// start a thread
    void start(void* function, void* args);

    /// native thread object
    ThreadObject m_thread;

    size_t m_id;
    /// dummy function. Holds a lambda that 
    /// calls the actual function
    rtl::function<void()> dummy;
};

} // radium


#endif // CORE_THREAD_H_