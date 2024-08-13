#ifndef RTL_ARRAY_TEST_H_
#define RTL_ARRAY_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/array.h"

#include "core/rtl/string.h"

TEST(rtl_test, array_test_primatives)
{
    rtl::array<int> test;
    test.resize(20);
    for (int i = 0; i < 20; i++)
        test.push_back(i);

    EXPECT_EQ(test.size(), 20);
    for (int i = 0; i < 20; i++)
    {
        ASSERT_EQ(test[i], i);
    }

    test.push_back(20);

    EXPECT_EQ(test[20], 20);

}

TEST(rtl_test, array_test_adt)
{
    rtl::array<rtl::string> test;

    char testdata[][10] =
    {
        "test1",
        "test2",
        "test3",
        "test4",
        "test5",
        "test6",
        "test7",
        "test8",
        "test9",
        "test10",
    };

    for (int i = 0; i < 10; i++)
    {
        test.push_back(rtl::move(testdata[i]));
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test[i] == testdata[i]);
        test[i] += "mod";
        EXPECT_TRUE(test[i] != testdata[i]);

    }

}


#endif // RTL_ARRAY_TEST_H_