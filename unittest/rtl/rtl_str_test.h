#ifndef RTL_STR_TEST_H_
#define RTL_STR_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/basic_string.h"
#include "core/rtl/string.h"

TEST(rtl_test, str_test_cow)
{
    rtl::string test = "hello";

    rtl::string test2 = test;

    EXPECT_EQ(test.c_str(), test2.c_str());

    test2 += "h";

    EXPECT_NE(test.c_str(), test2.c_str());

}

TEST(rtl_test, str_test_equality)
{
    rtl::string test1 = "hello";
    rtl::string test2 = "hello";

    EXPECT_EQ(test1, test2);

    test2 += "1";

    EXPECT_NE(test1, test2);

    rtl::string test3 = "privet komrad";

    EXPECT_EQ(test3, "privet komrad");
    
    test1 = "hello";
    test2 = "world";

    rtl::string test4 = test1 + test2;

    EXPECT_EQ(test4, "helloworld");

}

TEST(rtl_test, str_substr)
{
    rtl::string test = "#######privet komrad#######";

    rtl::string test2 = test.substr(7, 20);
    
    EXPECT_NE(test.c_str(), test2.c_str());

    EXPECT_EQ(test2, "privet komrad");

    test2 += ", stalin is waiting";
    EXPECT_TRUE(test2 == "privet komrad, stalin is waiting");

    rtl::string test3 = test2.substr(0, 6);

    EXPECT_TRUE(test3 == "privet");
}

TEST(rtl_test, str_misc)
{
    rtl::string test = "abcdefghijklmnopqrtstuvwxyz1234567890";

    EXPECT_TRUE(test[0] == 'a');
    EXPECT_TRUE(test.front() == 'a');
    
    EXPECT_TRUE(test.back() == '0');


}
#endif // RTL_STR_TEST_H_