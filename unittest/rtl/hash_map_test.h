#ifndef RTL_HASH_MAP_TEST_H_
#define RTL_HASH_MAP_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/hash_map.h"
#include "core/rtl/hash.h"

TEST(rtl_test, hash_map_primative)
{
    rtl::unordered_map<int, int> test;

    for (int i = 0; i < 10; i++)
    {
        test.insert({ i, i });
    }


    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test.contains(i));
    }

    test[1] = 100;

    EXPECT_TRUE(test.find(1)->second == 100);

    EXPECT_TRUE(test.find(1000000) == test.end());

}

TEST(rtl_test, hash_map_adt)
{
    rtl::unordered_map<rtl::string, rtl::string> test;

    test.insert({ "name", "bob" });
    test.insert({ "age", "75.1" });

    EXPECT_TRUE(test["name"] == "bob");

    test["name"] = "blob";
    EXPECT_TRUE(test["name"] == "blob");

    EXPECT_TRUE(test.find("sfasdfasdf") == test.end());
    EXPECT_TRUE(test.find("name") != test.end());

}

TEST(rtl_test, hash_map_remove_primitive)
{
    rtl::unordered_map<int, double> test;

    for (int i = 0; i < 10; i++)
        test.insert({ i, (double)(i / 3 )});

    EXPECT_TRUE(test.at(1) == 1 / 3);

    EXPECT_TRUE(test.find(5) != test.end());
    test.erase(5);
    EXPECT_TRUE(test.find(5) == test.end());

}


TEST(rtl_test, hash_map_remove_adt)
{
    rtl::unordered_map<rtl::string, rtl::string> test;
    test["bob"] = "person";
    test["name"] = "a";
    test["cat_name"] = "cat";

    EXPECT_STREQ(test["bob"].c_str(), "person");
    EXPECT_STREQ(test["name"].c_str(), "a");
    EXPECT_STREQ(test["cat_name"].c_str(), "cat");

    test.erase("bob");

    EXPECT_TRUE(test.find("bob") == test.end());
    // testing to make sure our ADTs don't get corrupted during moves
    EXPECT_STREQ(test["name"].c_str(), "a");
    EXPECT_STREQ(test["cat_name"].c_str(), "cat");


}
#endif // RTL_HASH_MAP_TEST_H_