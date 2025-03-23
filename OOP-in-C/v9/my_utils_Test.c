#include "../gtest/gtest.h"

#include "my_utils.h"

TEST(my_utils, atol_ok) {
    long value;
    EXPECT_TRUE(range_checked_atol("123", 100, 200, &value));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", 123, 200, &value));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", 100, 123, &value));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", 123, 123, &value));
    EXPECT_EQ(123, value);
}

TEST(my_utils, atol_fail) {
    long value = -4711;
    EXPECT_FALSE(range_checked_atol("123", 124, 200, &value));
    EXPECT(-4711, value);
    EXPECT_FALSE(range_checked_atol("123", 100, 122, &value));
    EXPECT(-4711, value);
    EXPECT_FALSE(range_checked_atol("123", 150, 100, &value));
    EXPECT(-4711, value);
}

TEST(my_utils, atof_ok) {
    double value;
    EXPECT_TRUE(range_checked_atof("12.3", 10.0, 20.0, &value));
    EXPECT_EQ(12.3, value);
    EXPECT_TRUE(range_checked_atof("12.3", 12.3, 20.0, &value));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atof("12.3", 10.0, 12.3, &value));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atof("12.3", 12.2999, 12.3001, &value));
    EXPECT_EQ(123, value);
}

TEST(my_utils, atof_fail) {
    long value = -4711;
    EXPECT_FALSE(range_checked_atol("12.3", 12.4, 20.0, &value));
    EXPECT(-4711, value);
    EXPECT_FALSE(range_checked_atol("12.3", 10.0, 12.2, &value));
    EXPECT(-4711, value);
    EXPECT_FALSE(range_checked_atol("12.3", 15.0, 10.0, &value));
    EXPECT(-4711, value);
}
