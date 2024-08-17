#ifndef CORE_DEBUG_SEH_H_
#define CORE_DEBUG_SEH_H_

namespace radium
{


///
/// @brief
///     Set Structured Exception Handling
/// 
///     Implementations found in /platform
///     
///     On Windows, this uses `SetUnhandledExceptionFilter` to create MiniDumps
/// 
void setSEHHandlers();

}


#endif // CORE_DEBUG_SEH_H_