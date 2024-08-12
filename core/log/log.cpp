#include "log.h"
#include <time.h>
#include <stdio.h>
#include <varargs.h>

using radium::Logger;

static const char* LogNameMap[5] =
{
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

void Logger::log(LogLevel ll, const char* msg, ...)
{
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
    output += LogNameMap[(int)ll];
    output += "] ";

    printf("%s\n",output.c_str());
    

}
