#include <core/system/timer.h>
#include <core/types.h>

#include <profileapi.h>

using radium::Timer;
using radium::I64;

Timer::Timer()
    : m_delta(0.0f), m_pausedTime(0), m_baseTime(0),
      m_prevTime(0), m_curTime(0), m_secPerCount(0.0f),
      paused(false), m_endTime(0)
{
    __int64 countPersec = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countPersec);
    m_secPerCount = 1.0f / (double)countPersec;
}

float Timer::getDelta() const
{
    return static_cast<float>(m_delta);
}

float Timer::getTotal() const
{
    if (paused)
        return (float)(((m_endTime - m_pausedTime) - m_baseTime) * m_secPerCount);
    else
        return (float)(((m_curTime - m_pausedTime) - m_baseTime) * m_secPerCount);

}

void Timer::reset()
{
    I64 currentTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

    paused = false;
    m_baseTime = currentTime;
    m_prevTime = currentTime;
    m_endTime = 0;

}

void Timer::start()
{
    I64 startTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    if (paused)
    {
        m_pausedTime += (startTime - m_endTime);
        m_prevTime = startTime;
        m_endTime = 0;
        paused = false;
    }

}

void Timer::stop()
{
    if (!paused)
    {
        I64 curTime;
        QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
        m_endTime   = curTime;
        paused      = true;
    }
}

void Timer::tick()
{
    if (paused)
    {
        m_delta = 0.0;
        return;
    }

    I64 curTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    m_curTime = curTime;
    m_delta = (curTime - m_prevTime) * m_secPerCount;
    m_prevTime = m_curTime;
    if (m_delta < 0.0f)
        m_delta = 0.0f;

}

