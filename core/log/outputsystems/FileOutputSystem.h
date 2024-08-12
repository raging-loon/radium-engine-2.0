#ifndef CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_
#define CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_

#include "OutputSystem.h"

#include "core/rtl/string.h"
#include "core/rtl/array.h"
namespace radium
{

class FileOutputSystem : public OutputSystem
{
public:

    FileOutputSystem(const rtl::string& name, int flushEveryNLogs);
    FileOutputSystem(const char* filename, int flushEveryNLogs);

    ~FileOutputSystem();

    bool supportsColor() override { return false; }

    void log(const rtl::string& msg) override;

    void flush() override;
private:

    int m_flushInterval;
    int m_curInterval;

    FILE* m_outFp;

    rtl::array<rtl::string> m_logCache;

    bool openFile(const char* name);
};

} // radium


#endif // CORE_LOG_OUTPUT_SYSTEMS_FILE_OUTPUT_SYSTEM_H_