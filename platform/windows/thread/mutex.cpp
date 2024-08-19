#include <platform/windows/win32platformtypes.h>
#include <core/error.h>
#include <core/thread/mutex.h>

#include <synchapi.h>
#include <stdio.h>
using radium::Mutex;
using radium::Status;

Mutex::Mutex()
    : m_mtx(nullptr)
{
}

Mutex::~Mutex()
{
    if (m_mtx)
        destroy();
}


Status Mutex::create()
{
    m_mtx = CreateMutex(
        NULL,
        FALSE,
        NULL
    );

    if (m_mtx == NULL)
    {
        printf("Mutex  creation error: %d\n", GetLastError());
        return ERR_INVALID_VALUE;
    }

    return OK;
}

void Mutex::destroy()
{
    if (m_mtx)
    {
        CloseHandle(m_mtx);
        m_mtx = nullptr;
    }
}

void Mutex::lock()
{
    // TODO: find better values
    WaitForSingleObject(m_mtx, INFINITE);
}

void Mutex::unlock()
{
    ReleaseMutex(m_mtx);
}