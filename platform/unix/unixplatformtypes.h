#ifndef PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_
#define PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_

#include <stdio.h>
#include <pthread.h>

namespace radium
{

using FileObject = FILE*;
using ThreadObject = pthread_t;

}

#endif // PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_