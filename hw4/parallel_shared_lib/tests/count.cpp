#include "count.h"

#include <gtest/gtest.h>

TEST(Parallel, EmptyData) {
    const auto got = getCharCounts({}, "abc");
    const std::vector<CharCount> expected {{'a', 0}, {'b', 0}, {'c', 0}};
    EXPECT_EQ(got, expected);
}

TEST(Parallel, EmptyCharset) {
    const auto got = getCharCounts({'a', 'b'}, "");
    EXPECT_TRUE(got.empty());
}

TEST(Parallel, SmallDataAndCharset) {
    const auto got = getCharCounts({'a', 'a', 'b', 'x', 'y'}, "abc");
    const std::vector<CharCount> expected {{'a', 2}, {'b', 1}, {'c', 0}};
    EXPECT_EQ(got, expected);
}

TEST(Parallel, MultipartDataWithCharset) {
    std::vector<unsigned char> bytes(4097);

    for (size_t i = 0; i < 4097; ++i) {
        bytes[i] = static_cast<unsigned char>('a') + (i % 3);
    }

    const auto got = getCharCounts(bytes, "acd");
    const std::vector<CharCount> expected {{'a', 1366}, {'c', 1365}, {'d', 0}};
    EXPECT_EQ(got, expected);
}
