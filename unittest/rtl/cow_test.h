#include "core/rtl/copy_on_write.h"
#include <gtest/gtest.h>

TEST(rtl_test, cow_test_1)
{
    rtl::copy_on_write<int> x;
    
    rtl::copy_on_write<int> y;
    x.resize(10);

    y = x;

    EXPECT_EQ(y.reference(), x.reference());
    y.resize(20);

    EXPECT_NE(y.reference(), x.reference());

}

struct __cow_d_test
{
    static int count;

    __cow_d_test()
    {
        count++;
    }

    ~__cow_d_test()
    {
        count--;
    }

};

int __cow_d_test::count = 0;

TEST(rtl_test, test_cow_destruction)
{
    {
        rtl::copy_on_write<__cow_d_test> test;
        test.resize(10);

        for (int i = 0; i < 10; i++)
        {
            auto* c = (test.at_pc(i));
            
            new (c) __cow_d_test;

        }
        EXPECT_EQ(__cow_d_test::count, 10);
    }
    EXPECT_EQ(__cow_d_test::count, 0);

}