#include "core/memory/Memory.h"
#include <assert.h>
using radium::Allocator;


constexpr uint64_t Allocator::get_pointer_adjustment_unsafe(void* ptr)
{
	assert(ptr);

	return *(uint64_t*)(get_pointer_base_unsafe(ptr));

}

constexpr void* Allocator::get_pointer_base_unsafe(void* ptr)
{
	assert(ptr);

	return ((void**)ptr)[-1];
}

void* Allocator::alloc_aligned(size_t size, size_t n, size_t alignment)
{
	assert((alignment & (alignment - 1)) == 0);



	void* addr = malloc((size * n) + alignment - 1 + sizeof(void*));

	uintptr_t aligned_addr = (uintptr_t)(addr) + sizeof(void*);

	aligned_addr = (aligned_addr + alignment - 1) & ~(alignment - 1);

	((void**)aligned_addr)[-1] = addr;
	

	return (void*)aligned_addr;
}

void Allocator::free_aligned(void* ptr)
{


	free(get_pointer_base_unsafe(ptr));
}
