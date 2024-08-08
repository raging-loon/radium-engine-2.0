#ifndef CORE_MEMORY_MEMORY_H_
#define CORE_MEMORY_MEMORY_H_

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

namespace radium
{

///
/// PURPOSE
///		Generic Aligned Memory allocator
///		
class Allocator
{
public:

	///
	/// PURPOSE
	///		Allocate (size * n) bytes that are aligned.
	/// 
	///		This will allocate an extra 4-8 bytes of memory
	///		You will receive the end of that 4-8 bytes.
	///		
	///		0			    64	  64 + sizeof data
	///		↓			    ↓			   ↓
	/// 	┌───────────────┬──────────────┐
	///		│  Raw Address  │ Aligned Addr │
	///		└───────────────┴──────────────┘
	///								↑
	///						You receive this
	///		 
	static void* alloc_aligned(size_t size, size_t n, size_t alignment);

	/// 
	/// PURPOSE
	///		Free aligned memory
	///		This will backtrack in memory
	/// 	
	///		┌───────────────┬──────────────┐
	///		│  Raw Address  │ Aligned Addr │
	///		└───────────────┴──────────────┘
	///			   ↑				↑
	///		Frees this address	Based on this address
	static void  free_aligned(void* ptr);

	static constexpr uint64_t get_pointer_adjustment_unsafe(void* ptr);

	static constexpr void* get_pointer_base_unsafe(void* ptr);
};



}


#endif // CORE_MEMORY_MEMORY_H_