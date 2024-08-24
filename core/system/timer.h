#ifndef CORE_SYSTEM_TIMER_H_
#define CORE_SYSTEM_TIMER_H_

#include <core/types.h>

namespace radium
{


///
/// @brief
///     Time keeper
///     Impl. found in /platform
class Timer
{
public:
    Timer();

    float getDelta() const;
    float getTotal() const;


    void reset();

    ///
    /// @brief
    ///     Starts the timer if it was paused
    ///     This will add the ammount of time paused
    ///     to the paused-time-counter
    /// 
    /// 
    ///                  |<--------pt------->|
    /// ----*------------*-------------------*------------->
    ///  m_baseTime  m_endTime           m_startTime           
    /// 
    /// pt is added to pause time
    /// 
    void start();

    /// Pause the timer
    /// Subsequent calls to tick will return 0
    void stop();

    /// increment the timer
    void tick();

private:
    double m_delta;

    I64 m_pausedTime;
    I64 m_baseTime;
    I64 m_prevTime;
    I64 m_curTime;
    I64 m_endTime;
#ifdef RADIUM_PLATFORM_WIN32
    double m_secPerCount;
#endif // RADIUM_PLATFORM_WIN32

    bool paused;
};

} // radium


#endif // CORE_SYSTEM_TIMER_H_