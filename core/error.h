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


#endif // CORE_ERROR_H_