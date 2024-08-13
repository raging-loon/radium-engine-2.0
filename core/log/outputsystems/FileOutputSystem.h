#ifndef CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_
#define CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_

#include "OutputSystem.h"

#include "core/rtl/string.h"
#include "core/rtl/array.h"
namespace radium
{

///
/// @brief
///     Write logs to a file
/// 
///     This will write logs to a file every <i>n</i> logs sent to it
///     This works by using an internal cache of recent logs (@ref m_logCache)
/// 
///     You can configure this in the constructor by setting the `flushEveryNLogs` parameter
/// 
///     Any remaining logs will automatically be flushed during destruction
/// 
class FileOutputSystem : public OutputSystem
{
public:

    FileOutputSystem(const rtl::string& name, int flushEveryNLogs);
    FileOutputSystem(const char* filename, int flushEveryNLogs);

    ~FileOutputSystem();

    /// not supported
    bool supportsColor() override { return false; }

    /// add msg to the log cache
    void log(const rtl::string& msg) override;

    /// Write logs to file
    void flush() override;
private:

    /// total number of log entries before flush
    int m_flushInterval;

    /// 
    /// @brief 
    ///     Current number of entries in cache.
    ///     Also used as an index for m_logCache.
    int m_curInterval;

    /// the file we are writing to
    FILE* m_outFp;

    /// array of logs, this will continually be overwritten
    rtl::array<rtl::string> m_logCache;

    bool openFile(const char* name);
};

} // radium


#endif // CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_