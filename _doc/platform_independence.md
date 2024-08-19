# Radium's Platform Independence Layer

Everything platform specific is under `/platform`

Under each major platform, there exists a file called `<platform-name>platformtypes.h`
This will include types like `ThreadObject`, `FileObject`. These are aliases for platform specific types such as `HANDLE` or `pthead_t`

## Platform Agnostic Interfaces

You will find several header files under `/core` that do not appear to have assocaited source files. These implementations are sunder `/platform`


