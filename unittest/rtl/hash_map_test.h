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

#endif // RTL_HASH_MAP_TEST_H_