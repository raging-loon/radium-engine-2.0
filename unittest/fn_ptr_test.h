#ifndef UNITTEST_FN_PTR_TEST_H_
#define UNITTEST_FN_PTR_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/function.h"
#include "core/rtl/string.h"

static int getSpecialNumber() { return 1234; }


TEST(rtl_test, function_ptr_test)
{

    rtl::function<int()> test = &getSpecialNumber;

    EXPECT_EQ(test.get(), getSpecialNumber);
    EXPECT_EQ(test(), 1234);


    rtl::function<int()> test2 = test;

    EXPECT_EQ(test.get(), test2.get());




}

#endif // UNITTEST_FN_PTR_TEST_H_