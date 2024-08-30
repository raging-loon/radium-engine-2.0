#ifndef CORE_TYPES_H_
#define CORE_TYPES_H_

#ifdef _WIN32
# include <platform/windows/win32platformtypes.h>
#elif defined(__linux__) || defined(__unix__)
# include <platform/unix/unixplatformtypes.h>
#else
# error "Unknown platform!"
#endif // _Win32

#include <stdint.h>

namespace radium
{

using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;

using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;

using U64 = uint64_t;
using I64 = int64_t;

using byte = unsigned char;


}

#endif // CORE_TYPES_H_