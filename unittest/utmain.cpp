#include <stdio.h>
#include <gtest/gtest.h>
#include "memory_tests.h"
#include "rtl_tests.h"
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}