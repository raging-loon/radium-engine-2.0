#ifndef CORE_DEBUG_LOG_H_
#define CORE_DEBUG_LOG_H_

#include "core/log/log.h"
#include "core/rtl/smart_ptr.h"
namespace radium
{

class GlobLoggers
{
public:

    static void init();

    static rtl::shared_ptr<Logger> getEngineLogger() { return m_engineLogger; }
    static rtl::shared_ptr<Logger> getClientLogger() { return m_clientLogger; }

private:
    static rtl::shared_ptr<Logger> m_engineLogger;
    static rtl::shared_ptr<Logger> m_clientLogger;

};

}


#endif // CORE_DEBUG_LOG_H_