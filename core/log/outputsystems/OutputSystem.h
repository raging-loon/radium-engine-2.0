#ifndef LOG_OUTPUT_SYSTEMS_OUTPUT_SYSTEM_H_
#define LOG_OUTPUT_SYSTEMS_OUTPUT_SYSTEM_H_

#include "core/rtl/string.h"

namespace radium
{

///
/// @brief
///     Base class for logging output
/// 
///     Any class derived from OutputSystem will be responsible for handling
///     out from @ref radium::Logger
/// 
class OutputSystem
{
public:
    /// Can we print with color? 
    virtual bool supportsColor() = 0;

    /// Handle the log
    virtual void log(const rtl::string& msg) = 0;

    /// Flush a list of logs if we maintian one
    virtual void flush() = 0;


    virtual ~OutputSystem() {}
};

}


#endif // LOG_OUTPUT_SYSTEMS_OUTPUT_SYSTEM_H_