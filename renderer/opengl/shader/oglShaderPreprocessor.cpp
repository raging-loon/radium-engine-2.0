#include "oglShaderPreprocessor.h"
#include <core/system/profiler.h>
using radium::oglShaderPreprocessor;

// this might look like a slow function but it has an average execution time
// of less than a millisecond
rtl::string oglShaderPreprocessor::extractSection(const char* name)
{
    //PROFILED_FUNCTION("extractSection");
    rtl::string line;
    line.resize(32);
    
    rtl::string extractedSection;
    extractedSection.resize(m_source.length() - m_position);
    rtl::string sectionName = "// !section ";
    sectionName += name;
    
    int sectionNameLength = sectionName.length() - 1;

    bool parsingSection = false;

    const char* source = m_source.c_str();
    while (*source)
    {
        // skip crlf bs
        if (*source == '\r')
            source++;

        if (*source == '\n')
        {
            // if we have multiple new lines in a row
            if (line.length() == 0)
            {
                source++;
                continue;
            }
            // break on the first endsection command if we are parsing
            if (parsingSection)
            {
                if (strncmp(line.c_str(), "// !endsection", 14) == 0)
                    break;
                else
                {
                    line += '\n';
                    extractedSection += line;
                }
            }
            // initiate parsing. strncmp so we don't have to add a zero to the end
            else if (strncmp(line.c_str(), sectionName.c_str(), sectionNameLength) == 0)
                parsingSection = true;
         
            line.setPos(1);

        }
        else
            line += *source;

        ++source;
    }
    
    if (!parsingSection)
        extractedSection.setPos(0);
    else
        extractedSection += '\0';
    
    
    return extractedSection;


}
