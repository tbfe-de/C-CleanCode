#include "../../gtest/gtest.h"

extern int foo();

TEST(testgroup_1, hgg_test)
{
    EXPECT_EQ(42, foo());
}
