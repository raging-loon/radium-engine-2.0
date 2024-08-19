#include <core/thread/thread.h>
#include <platform/unix/unixplatformtypes.h>

#include <pthread.h>

using radium::thread;
using radium::ThreadObject;

using PTHREAD_FUNCTION_PTR = void*(*)(void*);

void thread::start(void* function, void* args)
{
    pthread_t tid;

    int status = pthread_create(
        &tid, 
        NULL,
        (PTHREAD_FUNCTION_PTR)(function),
        args
    );

    m_id = (size_t)tid;
    m_thread = tid;
}

void thread::join()
{
    pthread_join(m_thread, NULL);
}

size_t thread::getId() const
{
    return static_cast<size_t>(m_id);
}

size_t thread::getThreadID()
{
    return static_cast<size_t>(pthread_self());
}