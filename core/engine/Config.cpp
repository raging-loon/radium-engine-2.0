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
//
//ConfigVar& Config::operator[](const rtl::string& key)
//{
//    // TODO: insert return statement here
//}
//
//const ConfigVar& Config::operator[](const rtl::string& key) const
//{
//    // TODO: insert return statement here
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
    source.resize(file.getSize() + 1);
    
    source.setPos(file.getSize());

    file.read(source.data(), file.getSize() + 1, nullptr);

    return OK;
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
