#include "FileOutputSystem.h"
#include <stdarg.h>
#include <stdio.h>
using radium::FileOutputSystem;

FileOutputSystem::FileOutputSystem(const rtl::string& name, int flushEveryNLogs)
    : FileOutputSystem(name.c_str(), flushEveryNLogs)
{
      
}

FileOutputSystem::FileOutputSystem(const char* filename, int flushEveryNLogs)
    : m_flushInterval(flushEveryNLogs), m_curInterval(0), m_outFp(nullptr)
{
    m_logCache.resize(m_flushInterval);
    // TODO: add error message and default to stderr
    openFile(filename);
}

FileOutputSystem::~FileOutputSystem()
{
    if(m_file.isOpen())
        flush();

    // resize to whatever current interval is. 
    // This will ensure unitialized strings are not destructed
    // Might not be super efficient, but ideally loggers
    // won't be created and destroyed many times.s
    m_logCache.resize(m_curInterval);
}

void FileOutputSystem::log(const rtl::string& msg)
{
    
    m_logCache[m_curInterval] = msg;

    ++m_curInterval;
    
    if (m_curInterval >= m_flushInterval)
    {
        flush();
        m_curInterval = 0;
    }

}


void FileOutputSystem::flush()
{
    printf("flushing\n");
    for (int i = 0; i < m_curInterval; i++)
    {
        m_file.write(m_logCache[i].c_str(), 1, m_logCache[i].length() - 1);
    }
}

bool FileOutputSystem::openFile(const char* name)
{
    return m_file.open(name, File::APPEND) == Status::OK;
}
