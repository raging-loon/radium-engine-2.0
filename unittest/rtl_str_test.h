#ifndef RTL_STR_TEST_H_
#define RTL_STR_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/basic_string.h"
#include "core/rtl/string.h"

TEST(rtl_test, rtl_str_test)
{
    rtl::string test = "hello";

    rtl::string test2 = test;

    EXPECT_EQ(test.c_str(), test2.c_str());

    test2 += "h";

    EXPECT_NE(test.c_str(), test2.c_str());

}

#endif // RTL_STR_TEST_H_