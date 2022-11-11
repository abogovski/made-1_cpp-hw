#include <gtest/gtest.h>

extern "C" {
#include "body.h"
}

TEST(body, fromString) {
    EXPECT_EQ(bodyFromString("minivan"), Minivan);
    EXPECT_EQ(bodyFromString(""), Undefined);
    EXPECT_EQ(bodyFromString("no-such-body"), Undefined);
}

TEST(body, toString) {
    EXPECT_STREQ(bodyToString(Minivan), "minivan");
    EXPECT_EQ(bodyToString(Undefined), nullptr);
}
