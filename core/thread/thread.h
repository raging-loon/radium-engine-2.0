#ifndef CORE_THREAD_H_
#define CORE_THREAD_H_

#include <core/types.h>
#include <core/rtl/utility.h>
#include <Windows.h> // TEMPL CODE: TODO REMOVE
#include <stdio.h>

#include <core/rtl/function2.h>
namespace radium
{

class dummy_thread_runner
{
public:
    static void* run(void* p)
    {
        auto* fn = static_cast<rtl2::function<void()>*>(p);
        (*fn)();

        return nullptr;
    }
};

class thread
{
public:

    template<class T, class ...Args>
    explicit thread(T&& t, Args&&... args)
    {
        dummy = [=]() mutable {
            rtl::forward<T>(t)(rtl::forward<Args>(args)...);
        };
        DWORD id;
        start(dummy_thread_runner::run, (void*)&dummy);
        //CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(dummy_thread_runner::run), (void*)&dummy, 0, &id);
    }

private:

    void start(void* function, void* args)
    {
        auto fn = reinterpret_cast<LPTHREAD_START_ROUTINE>(function);
        DWORD id;
        m_thread = CreateThread(NULL, 0, fn, args, 0, &id);
        if (m_thread == NULL)
        {
            printf("null\n");
            return;
        }
        WaitForSingleObject(m_thread, INFINITE);
        CloseHandle(m_thread);
    }

    void* threadRunner(void* f)
    {
      
    }

    ThreadObject m_thread;
    size_t m_id;
    rtl2::function<void()> dummy;
};

} // radium


#endif // CORE_THREAD_H_