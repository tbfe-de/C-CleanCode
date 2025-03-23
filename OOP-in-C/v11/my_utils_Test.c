#include "../gtest/gtest.h"

#include "my_utils.h"

TEST(utils_checked, atol_ok) {
    long value = -4711;
    EXPECT_TRUE(range_checked_atol("123", &value, 100, 200));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", &value, 123, 200));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", &value, 100, 123));
    EXPECT_EQ(123, value);
    EXPECT_TRUE(range_checked_atol("123", &value, 123, 123));
    EXPECT_EQ(123, value);
}

TEST(utils_checked, atol_fail) {
    long value = -4711;
    EXPECT_FALSE(range_checked_atol("123", &value, 124, 200));
    EXPECT_EQ(-4711, value);
    EXPECT_FALSE(range_checked_atol("123", &value, 100, 122));
    EXPECT_EQ(-4711, value);
    EXPECT_FALSE(range_checked_atol("123", &value, 150, 100));
    EXPECT_EQ(-4711, value);
}

TEST(utils_checked, atof_ok) {
    double value = -47.11;
    EXPECT_TRUE(range_checked_atof("12.3", &value, 10.0, 20.0));
    EXPECT_DOUBLE_EQ(12.3, value);
    EXPECT_TRUE(range_checked_atof("12.3", &value, 12.3, 20.0));
    EXPECT_DOUBLE_EQ(12.3, value);
    EXPECT_TRUE(range_checked_atof("12.3", &value, 10.0, 12.3));
    EXPECT_DOUBLE_EQ(12.3, value);
    EXPECT_TRUE(range_checked_atof("12.3", &value, 12.2999, 12.3001));
    EXPECT_DOUBLE_EQ(12.3, value);
}

TEST(utils_checked, atof_fail) {
    double value = -47.11;
    EXPECT_FALSE(range_checked_atof("12.3", &value, 12.4, 20.0));
    EXPECT_DOUBLE_EQ(-47.11, value);
    EXPECT_FALSE(range_checked_atof("12.3", &value, 10.0, 12.2));
    EXPECT_DOUBLE_EQ(-47.11, value);
    EXPECT_FALSE(range_checked_atof("12.3", &value, 15.0, 10.0));
    EXPECT_DOUBLE_EQ(-47.11, value);
}

TEST(utils_slist, atol_ok) {
    long a, b, c;
    struct string_list_atol_ctl ctltab[] = {
        {&a, 10, 20},
        {&b, 10, 20},
        {&c, 10, 20},
        {NULL}
    };
    const size_t nparsed = string_list_atol(" 17  19   11", ctltab);
    EXPECT_EQ(3, nparsed);
    EXPECT_EQ(17, a);
    EXPECT_EQ(19, b);
    EXPECT_EQ(11, c);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[1].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[2].fail);
}

TEST(utils_slist, atol_fail) {
    long a, b, c;
    size_t nparsed;
    struct string_list_atol_ctl ctltab[] = {
        {&a, 10, 20},
        {&b, 10, 20},
        {&c, 10, 20},
        {NULL}
    };

    nparsed = string_list_atol(" 17  1x   11", ctltab);
    EXPECT_EQ(1, nparsed);
    EXPECT_EQ(17, a);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_nn, ctltab[1].fail);

    nparsed = string_list_atol(" 17  1   11", ctltab);
    EXPECT_EQ(nparsed, 1);
    EXPECT_EQ(17, a);
    EXPECT_EQ(string_list_err_lo, ctltab[1].fail);

    nparsed = string_list_atol(" 17  19  21", ctltab);
    EXPECT_EQ(2, nparsed);
    EXPECT_EQ(17, a);
    EXPECT_EQ(19, b);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[1].fail);
    EXPECT_EQ(string_list_err_hi, ctltab[2].fail);
}

TEST(utils_slist, atof_ok) {
    double a, b, c;
    struct string_list_atof_ctl ctltab[] = {
        {&a, 1.0, 2.0},
        {&b, 1.0, 2.0},
        {&c, 1.0, 2.0},
        {NULL}
    };
    const size_t nparsed = string_list_atof(" 1.7  1.9   1.1", ctltab);
    EXPECT_EQ(3, nparsed);
    EXPECT_NEAR(1.7, a, 1e-6);
    EXPECT_NEAR(1.9, b, 1e-6);
    EXPECT_NEAR(1.1, c, 1e-6);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[1].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[2].fail);
}

TEST(utils_slist, atof_fail) {
    double a, b, c;
    size_t nparsed;
    struct string_list_atof_ctl ctltab[] = {
        {&a, 1.0, 2.0},
        {&b, 1.0, 2.0},
        {&c, 1.0, 2.0},
        {NULL}
    };

    nparsed = string_list_atof(" 1.7  1x   1.1", ctltab);
    EXPECT_EQ(1, nparsed);
    EXPECT_NEAR(1.7, a, 1e-6);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_nn, ctltab[1].fail);

    nparsed = string_list_atof(" 1.7  0.999   1.1", ctltab);
    EXPECT_DOUBLE_EQ(1, nparsed);
    EXPECT_NEAR(1.7, a, 1e-6);
    EXPECT_EQ(string_list_err_lo, ctltab[1].fail);

    nparsed = string_list_atof(" 1.7  1.0  2.001", ctltab);
    EXPECT_EQ(2, nparsed);
    EXPECT_NEAR(1.7, a, 1e-6);
    EXPECT_NEAR(1.0, b, 1e-6);
    EXPECT_EQ(string_list_err_ok, ctltab[0].fail);
    EXPECT_EQ(string_list_err_ok, ctltab[1].fail);
    EXPECT_EQ(string_list_err_hi, ctltab[2].fail);
}
