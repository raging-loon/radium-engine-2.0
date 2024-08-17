#include <core/debug/seh.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>

void radium::setSEHHandlers()
{
    // local version of `ulimit -c unlimited`
    // This will ensure if there is a crash,
    // the core will be dumped
    struct rlimit proc_core_limit;

    proc_core_limit.rlim_cur = RLIM_INFINITY;
    proc_core_limit.rlim_max = RLIM_INFINITY;

    if(setrlimit(RLIMIT_CORE, &proc_core_limit) != 0)
    {
        printf("Failed to set RLIMIT_CORE. Crashes may not core dump\n");
    }

}