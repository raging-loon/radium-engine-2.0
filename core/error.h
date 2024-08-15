#ifndef CORE_ERROR_H_
#define CORE_ERROR_H_

#include <assert.h>

#ifdef _MSC_VER
#define UNREACHABLE \
{\
printf("UNREACHABLE CODE REACHED: %s @ %s:%d\n", __FUNCSIG__, __FILE__, __LINE__);\
abort();\
}
#else
#define UNREACHABLE \
{\
printf("UNREACHABLE CODE REACHED: %s @ %s:%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);\
abort();\
}
#endif

namespace radium
{

enum Status
{
    OK,
    ERR_FILE_OPEN,
    ERR_FILE_NOT_EXIST,
    ERR_INVALID_VALUE
};


} // radium





#endif // CORE_ERROR_H_