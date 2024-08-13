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
    if(m_outFp)
    {
        flush();
        fclose(m_outFp);
    }
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
        fprintf(m_outFp, m_logCache[i].c_str());
    }
}

bool FileOutputSystem::openFile(const char* name)
{
    FILE* fp = fopen(name, "w");

    if (!fp)
        return false;

    m_outFp = fp;

    return true;
}
