﻿#ifndef CORE_MEMORY_MEMORY_H_
#define CORE_MEMORY_MEMORY_H_

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

namespace radium
{

///
/// @class
///    Generic Aligned Memory allocator
///    
class GenericAllocator
{
public:

    static void* alloc_static(size_t size);
    static void  free_static(void* ptr);


    /// 
    ///    Allocate (size * n) bytes that are aligned.
    /// 
    ///    This will allocate an extra 4-8 bytes of memory
    ///    You will receive the end of that 4-8 bytes.
    ///    @code
    ///    0                64                128
    ///    ↓                ↓               ↓
    ///    ┌───────────────┬──────────────┐
    ///    │  Raw Address  │ Aligned Addr │
    ///    └───────────────┴──────────────┘
    ///                            ↑
    ///                    You receive this
    ///    @endcode     

    static void* alloc_aligned(size_t size, size_t n, size_t alignment);
    static void* alloc_aligned(size_t size, size_t alignment);
    /// 
    /// @details
    /// 
    ///    Free aligned memory
    ///    This will backtrack in memory
    /// @code
    ///    ┌───────────────┬──────────────┐
    ///    │  Raw Address  │ Aligned Addr │
    ///    └───────────────┴──────────────┘
    ///           ↑                ↑
    ///    Frees this address    Based on this address
    ///    @endcode
    ///
    static void  free_aligned(void* ptr);

    template <class T>
    static constexpr T* alloc_aligned(size_t n)
    {
        if constexpr (sizeof(T) < 4)
            return (T*)alloc_aligned(n, 4);
        else
            return (T*)alloc_aligned(n, alignof(T));

    }


};










}


#endif // CORE_MEMORY_MEMORY_H_