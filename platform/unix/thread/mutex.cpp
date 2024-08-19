#include <platform/unix/unixplatformtypes.h>
#include <core/error.h>
#include <core/error.h>
#include <core/thread/mutex.h>
#include <pthread.h>
#include <errno.h>


using radium::Mutex;
using radium::Status;

Mutex::Mutex()
    : m_mtx{-1}
{
}

Mutex::~Mutex()
{
    destroy();
}

Status Mutex::create()
{
    int createStatus;
    pthread_mutexattr_t mtxAttr;

    pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_RECURSIVE);    

    createStatus = pthread_mutex_init(&m_mtx, &mtxAttr);

    if(createStatus == 0)
        return OK;

    switch(createStatus)
    {
        case ENOMEDIUM:
            return ERR_OUT_OF_MEMORY;
        case EBUSY:
            return ERR_THREAD_BUSY;
        case EPERM:
            return ERR_ACCESS_DENIED;
        case EINVAL:
            return ERR_INVALID_VALUE;
        default:
            return ERR_UNSPECIFIED;
    }
}

void Mutex::lock()
{
    pthread_mutex_lock(&m_mtx);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&m_mtx);
}

void Mutex::destroy()
{
    pthread_mutex_destroy(&m_mtx);  
}