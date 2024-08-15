#ifndef RTL_HASH_MAP_TEST_H_
#define RTL_HASH_MAP_TEST_H_

#include <gtest/gtest.h>
#include "core/rtl/hash_map.h"
#include "core/rtl/hash.h"

TEST(rtl_test, hash_map_primative)
{
    rtl::hash_map<int, int> test;
}

#endif // RTL_HASH_MAP_TEST_H_