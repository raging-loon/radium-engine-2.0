#include "globlog.h"

#include <core/log/outputsystems/StdOutSystem.h>
#include <core/system/profiler.h>

using radium::Logger;
using radium::GlobLoggers;
using rtl::shared_ptr;

shared_ptr<Logger> GlobLoggers::m_clientLogger;
shared_ptr<Logger> GlobLoggers::m_engineLogger;

void GlobLoggers::init()
{
    m_engineLogger = rtl::make_shared<Logger>("ENGINE");
    m_clientLogger = rtl::make_shared<Logger>("CLIENT");

    m_engineLogger->setOutputSystem<radium::StdoutSystem>();
    m_clientLogger->setOutputSystem<radium::StdoutSystem>();
}
