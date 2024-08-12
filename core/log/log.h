#ifndef CORE_LOG_LOG_H_
#define CORE_LOG_LOG_H_

#include "core/rtl/string.h"
#include "core/rtl/utility.h"
#include "core/log/colors.h"
namespace radium
{

enum class LogLevel : int
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};


///
/// @brief 
///     Logging Class
/// 
///     The Logger class is responsible for constructing output
/// 
///     The OutputSystem is responsible for what happens with 
///     E.g. console output, file output, etc
/// 
class Logger
{
public:
    
   

public:

    Logger(const rtl::string& name) : m_name(rtl::move(name)) {}
    Logger(const char* name) : m_name(name) {}


    void log(LogLevel ll, const char* msg, ...);

private:

    rtl::string m_name;

    const char* m_colorMap[5] =
    {
        {Colors::GREEN},
        {Colors::GREEN},
        {Colors::YELLOW},
        {Colors::RED},
        {Colors::RED}
    };

};


} // radium


#endif //CORE_LOG_LOG_H_