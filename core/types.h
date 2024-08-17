#ifndef CORE_TYPES_H_
#define CORE_TYPES_H_

#ifdef _WIN32
#include <windows.h>
#else
# include <stdio.h>
#endif // _WIN32

namespace radium
{

#ifdef _WIN32

using FileObject = HANDLE;
#elif defined(__linux__) || defined(__unix__)
using FileObject = FILE*;
#endif // _WIN32


} // radium


#endif // CORE_TYPES_H_