#include <gtest/gtest.h>
#include "core/memory/Memory.h"

TEST(MemoryTest, AlignmentTest)
{
	int* myIntArray = radium::Allocator::alloc_aligned<int>(10);

	

#error
}