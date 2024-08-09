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

