#ifndef CORE_ENGINE_APPLICATION_H_
#define CORE_ENGINE_APPLICATION_H_

#include <core/rtl/string.h>
#include <core/error.h>

namespace radium
{

class Application
{
public:

    Status init(const char* filename = nullptr);



private:

    rtl::string m_appName;




};


} // radium


#endif // CORE_ENGINE_APPLICATION_H_