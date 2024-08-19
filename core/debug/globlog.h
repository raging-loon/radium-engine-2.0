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

#define ENGINE_INFO(...)       radium::GlobLoggers::getEngineLogger()->info(__VA_ARGS__) 
#define ENGINE_DEBUG(...)      radium::GlobLoggers::getEngineLogger()->debug(__VA_ARGS__) 
#define ENGINE_WARNING(...)    radium::GlobLoggers::getEngineLogger()->warning(__VA_ARGS__)     
#define ENGINE_ERROR(...)      radium::GlobLoggers::getEngineLogger()->error(__VA_ARGS__) 
#define ENGINE_CRITICAL(...)   radium::GlobLoggers::getEngineLogger()->critcal(__VA_ARGS__)     


#endif // CORE_DEBUG_LOG_H_