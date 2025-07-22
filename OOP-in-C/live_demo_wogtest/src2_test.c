#include "../../gtest/gtest.h"

extern double one_third();
extern double PI();

TEST(testgroup_2,  one_third_test)
{
    EXPECT_DOUBLE_EQ(0.333333, one_third());
}

TEST(testgroup_2, PI_test)
{
    EXPECT_DOUBLE_EQ(3.14159, PI());
}
