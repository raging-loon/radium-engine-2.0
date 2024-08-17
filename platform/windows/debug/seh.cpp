#include "core/debug/seh.h"

#include <Windows.h>
#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp.lib")



static LONG WINAPI FatalExceptionHandler(EXCEPTION_POINTERS* plist);
static void WriteMiniDump(EXCEPTION_POINTERS* plist);


void radium::setSEHHandlers()
{
    SetUnhandledExceptionFilter(FatalExceptionHandler);
}

LONG WINAPI FatalExceptionHandler(EXCEPTION_POINTERS* plist)
{
    WriteMiniDump(plist);
    return EXCEPTION_EXECUTE_HANDLER;
}

void WriteMiniDump(EXCEPTION_POINTERS* plist)
{
    HANDLE dumpfile = CreateFile(
        "minidump.dmp", 
        GENERIC_WRITE, 0, NULL, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    if (dumpfile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo =
        {
            .ThreadId = GetCurrentThreadId(),
            .ExceptionPointers = plist,
            .ClientPointers = TRUE
        };

        MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            dumpfile,
            MiniDumpNormal,
            &dumpInfo,
            NULL,
            NULL
        );

        CloseHandle(dumpfile);
    }
}
