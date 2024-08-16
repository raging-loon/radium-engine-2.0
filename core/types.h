#ifndef CORE_TYPES_H_
#define CORE_TYPES_H_

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace radium
{

#ifdef _WIN32

using FileObject = HANDLE;

#endif // _WIN32


} // radium


#endif // CORE_TYPES_H_