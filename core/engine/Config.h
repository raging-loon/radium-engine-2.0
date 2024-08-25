#ifndef CORE_ENGINE_CONFIG_H_
#define CORE_ENGINE_CONFIG_H_

#include <core/rtl/variant.h>
#include <core/rtl/string.h>
#include <core/rtl/hash_map.h>
#include <core/error.h>

namespace radium
{

using ConfigVar = rtl::variant< rtl::typelist<int, double, rtl::string> >;


///
/// @brief
///     A general key value configuration object
/// 
class Config
{
public:

    Config();
    ~Config();

    ConfigVar& operator[](const rtl::string& key);
    const ConfigVar& operator[](const rtl::string& key) const;
    
    Status readConfigFromFile(const char* filename);

    Status readConfigFromString(const rtl::string& source);

    Status writeConfigToFile(const char* filename = nullptr);

    Status writeConfigToString(rtl::string& output);

private:

    rtl::string m_filename;

    rtl::unordered_map<rtl::string, ConfigVar > m_cfgMap;
};

} // radium

#endif // CORE_ENGINE_CONFIG_H_