#include <stdio.h>
#include <gtest/gtest.h>
#include "rtl_tests.h"
#include <glm.hpp>
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}