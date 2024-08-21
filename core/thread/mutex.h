#ifndef CORE_THREAD_MUTEX_H_
#define CORE_THREAD_MUTEX_H_

#include <core/types.h>
#include <core/error.h>
namespace radium
{


///
/// @brief 
///     Mutual Exclusion 
/// 
///     Wrapper around OS thread-api Mutexes (e.g. windows Mutexes and pthreads)
/// 
///     Implementations found under /platform/<platform>/thread/thread.cpp
/// 
class Mutex
{
public:

    Mutex();

    /// This will destroy a mutex if 
    /// it's been createds
    ~Mutex();

    /// Create a new mutex
    Status create();

    /// Destory the mutex
    void destroy();

    /// lock
    void lock();

    /// unlock
    void unlock();

private:
    /// HANDLE on win32, pthread_mutex_t on linux
    MutexObject m_mtx;
};


/// 
/// @brief
///     Auto locks/unlocks mutexes 
///     Should only be used inside of functions
/// 
class ScopedMutexLocker
{
public:
    ScopedMutexLocker(Mutex& m)
        : m_mutex(m)
    {
        m_mutex.lock();
    }

    ~ScopedMutexLocker()
    {
        m_mutex.unlock();
    }

private:
    Mutex& m_mutex;
};

} // radium


#endif // CORE_THREAD_MUTEX_H_