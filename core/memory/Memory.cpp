#include "core/memory/Memory.h"
#include <assert.h>
using radium::GenericAllocator;



void* GenericAllocator::alloc_static(size_t size)
{
    return malloc(size);
}

void GenericAllocator::free_static(void* ptr)
{
    return free(ptr);
}

void* GenericAllocator::alloc_aligned(size_t size, size_t n, size_t alignment)
{
    assert((alignment & (alignment - 1)) == 0);
#ifdef _MSC_VER
    return _aligned_malloc(size * n, alignment);
#endif
}

void* radium::GenericAllocator::alloc_aligned(size_t size, size_t alignment)
{
    assert((alignment & (alignment - 1)) == 0);
#ifdef _MSC_VER
    return _aligned_malloc(size, alignment);
#endif
}

void GenericAllocator::free_aligned(void* ptr)
{
#ifdef _MSC_VER
    return _aligned_free(ptr);
#endif 
}
