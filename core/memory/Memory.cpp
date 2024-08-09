#include "core/memory/Memory.h"
#include <assert.h>
using radium::Allocator;



void* Allocator::alloc_aligned(size_t size, size_t n, size_t alignment)
{
	assert((alignment & (alignment - 1)) == 0);



	void* addr = malloc((size * n) + alignment - 1 + sizeof(void*));

	uintptr_t aligned_addr = (uintptr_t)(addr) + sizeof(void*);

	aligned_addr = (aligned_addr + alignment - 1) & ~(alignment - 1);

	((void**)aligned_addr)[-1] = addr;
	

	return (void*)aligned_addr;
}

void* radium::Allocator::alloc_aligned(size_t size, size_t alignment)
{
	assert((alignment & (alignment - 1)) == 0);



	void* addr = malloc((size + alignment - 1 + sizeof(void*)));

	uintptr_t aligned_addr = (uintptr_t)(addr)+sizeof(void*);

	aligned_addr = (aligned_addr + alignment - 1) & ~(alignment - 1);

	((void**)aligned_addr)[-1] = addr;


	return (void*)aligned_addr;
}

void Allocator::free_aligned(void* ptr)
{
	void* addr = get_pointer_base_unsafe(ptr);
	free(addr);
}
