#ifndef CORE_LOG_OUTPUT_SYSTEMS_STD_OUT_SYSTEM_H_
#define CORE_LOG_OUTPUT_SYSTEMS_STD_OUT_SYSTEM_H_

#include "OutputSystem.h"

namespace radium
{

///
/// @brief
///     Print logs to an output stream such as stdout
/// 
///     By default, all logs will be sent to stderr
///     however, this can be configured via the constructor
/// 
///     You <i>can</i> pass a FILE pointer to a file you created, 
///     e.g. 'log.txt', however this is not recommended, as formatting with
///     color may screw with your output
///     Instead, it is recommended to use @ref FileOutoutSystem
///     
/// 
class StdoutSystem : public OutputSystem
{
public:

    StdoutSystem(FILE* fp = stderr) : m_opfp(fp) {}

    /// Yes we support color
    bool supportsColor() override { return true; }

    /// send @ref msg.c_str() to @ref m_opfp
    void log(const rtl::string& msg) override;

    /// not implemented here
    void flush() override;

private:
    /// output file pointer
    FILE* m_opfp;
};

} // radium


#endif // CORE_LOG_OUTPUT_SYSTEMS_STD_OUT_SYSTEM_H_