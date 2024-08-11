#include <gtest/gtest.h>
#include "core/memory/Memory.h"

TEST(MemoryTest, AlignmentTest)
{
    int* myIntArray = radium::GenericAllocator::alloc_aligned<int>(10);

    EXPECT_EQ(
        (uintptr_t)myIntArray, 
        ((uintptr_t)radium::GenericAllocator::get_pointer_base_unsafe(myIntArray) + 
                    radium::GenericAllocator::get_num_bytes_aligned_unsafe(myIntArray))
    );
    
    radium::GenericAllocator::free_aligned(myIntArray);
}

