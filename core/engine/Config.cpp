#include "Config.h"

#include <core/rtl/variant.h>
#include <core/rtl/string.h>
#include <core/error.h>
#include <core/io/file.h>

using radium::Config;
using radium::ConfigVar;
using radium::Status;

Config::Config()
{
}

Config::~Config()
{
}

ConfigVar& Config::operator[](const rtl::string& key)
{
    return m_cfgMap[key];
}

//const ConfigVar& Config::operator[](const rtl::string& key) const
//{
//}


Status Config::readConfigFromFile(const char* filename)
{
    File file;
    Status openStat = file.open(filename, File::AccessMode::READ);
    
    if (openStat != OK)
        return openStat; 

    if (!file.isOpen())
        return ERR_FILE_IO;

    m_filename = filename;

    rtl::string source;
  
    size_t fileSize = file.getSize();
    
    source.resize(fileSize + 1);
    source.setPos(fileSize);

    file.read(source.data(), fileSize + 1, nullptr);
    
    source[fileSize] = 0;

    
    return parseConfig(source);
}

Status Config::readConfigFromString(const rtl::string& source)
{
    return Status();
}

Status Config::writeConfigToFile(const char* filename)
{
    return Status();
}

Status Config::writeConfigToString(rtl::string& output)
{
    return Status();
}

Status Config::parseConfig(const rtl::string& cfg)
{
    rtl::string line;
    line.resize(64);
    line.setPos(0);

    size_t cfglen = cfg.length();

    bool skipLine = false;

    size_t linepos = 0;
    
    // This will skip over any '[', '\r', and '#' characters/lines
    // when it reaches a new line or the end of the file, it will parse the previous line
    // Otherwise it will add characters to the current line
    // <= so we can grab the last line (it might not end with a newline)
    for (int i = 0; i <= cfglen; i++)
    {
        char cur = cfg[i];
        
        if (cur == '\r')
            continue;

        if (skipLine && cur != '\n')
            continue;

        if (cur == '#' || cur == '[')
            skipLine = true;
        
        else if (cur == '\n' || i == cfglen)
        {
            if(skipLine) skipLine = false;
            if (linepos == 0)
                continue;
            
            line[linepos] = '\0';
            Status pslstat = parseSingleLine(line);
            if (pslstat != OK)
                return pslstat;

            linepos = 0;
        }
        else
        {
            if (!skipLine)
                line[linepos++] = cur;
        }

        if (line.length() - 1 <= linepos)
            line.resize(linepos + 64);
    }

    return OK;

}

Status Config::parseSingleLine(const rtl::string& line)
{
    rtl::string key;
    key.resize(32);
    // points to position in line that is start of value
    const char* valueptr = nullptr;

    const char* cfgline = line.c_str();

    while (*cfgline)
    {
        if (*cfgline == '=') 
        {
            valueptr = cfgline + 1;
            break;
        }
        else
            key += *cfgline;
        cfgline++;
    }
    if (!valueptr)
        return ERR_INVALID_VALUE;
    key += '\0';
    ConfigVar& var = m_cfgMap[key];
    
    
    if (strcmp(valueptr, "true") == 0)
        var.set(true);
    else if (strcmp(valueptr, "false") == 0)
        var.set(false);
    else if (rtl::is_integer(valueptr))
        var.set(atoi(valueptr));
    else if (rtl::is_float(valueptr))
        var.set(atof(valueptr));
    else if (valueptr[0] == '\"' || valueptr[0] == '\'')
    {
        var.set(rtl::string(valueptr + 1));
        rtl::string& val = var.as < rtl::string>();
        // overwrite the " or ' the end
        val.back() = '\0';
    }

    return OK;
}
