#include "log.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

using radium::Logger;

static const char* LogNameMap[5] =
{
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

Logger::~Logger()
{
    if (m_outputSystem)
        delete m_outputSystem;
}

void Logger::log(LogLevel ll, const char* msg, ...)
{
    assert(m_outputSystem);

    rtl::string output;
    
    char timeBuffer[25];
    output.resize(
        // 10 for max size of lognamemap var
        27 + m_name.length() + 25
    );
    time_t timeOfLog = time(NULL);
    struct tm* timeInfo = nullptr;
    timeInfo = localtime(&timeOfLog);

    strftime(timeBuffer, 24, "[%F %T]", timeInfo);
    timeBuffer[24] = 0;
    output += timeBuffer;

    output += " [";
    output += m_name;
    output += "]";


    output += " [";

    if (m_outputSystem->supportsColor())
    {
        output += m_colorMap[(int)ll];
        output += LogNameMap[(int)ll];
        output += Colors::CLEAR;
    }
    else
    {
        output += LogNameMap[(int)ll];
    }
    output += "] ";

    char temp[256] = { 0 };
    va_list args;
    va_start(args, msg);

    vsnprintf_s(temp, 256, msg, args);
    va_end(args);

    output += temp;
    output += "\n";

    m_outputSystem->log(output);
}



