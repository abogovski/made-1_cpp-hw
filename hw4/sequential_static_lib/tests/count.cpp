#include "count.h"

#include <gtest/gtest.h>

TEST(Sequential, EmptyData) {
    const auto got = getCharCounts({}, "abc");
    const std::vector<CharCount> expected {{'a', 0}, {'b', 0}, {'c', 0}};
    EXPECT_EQ(got, expected);
}

TEST(Sequential, EmptyCharset) {
    const auto got = getCharCounts({'a', 'b'}, "");
    EXPECT_TRUE(got.empty());
}

TEST(Sequential, SmallDataAndCharset) {
    const auto got = getCharCounts({'a', 'a', 'b', 'x', 'y'}, "abc");
    const std::vector<CharCount> expected {{'a', 2}, {'b', 1}, {'c', 0}};
    EXPECT_EQ(got, expected);
}
