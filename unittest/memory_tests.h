#include <gtest/gtest.h>
#include "core/memory/Memory.h"

TEST(MemoryTest, AlignmentTest)
{
    int* myIntArray = radium::Allocator::alloc_aligned<int>(10);

    EXPECT_EQ(
        (uintptr_t)myIntArray, 
        ((uintptr_t)radium::Allocator::get_pointer_base_unsafe(myIntArray) + 
                    radium::Allocator::get_num_bytes_aligned_unsafe(myIntArray))
    );
    
    radium::Allocator::free_aligned(myIntArray);
}

