#include "../gtest/gtest.h"

// if more test groups are required define
// TESTCASE-s accordingly in `unit_Test.c`

#include "DDD_HH_MM_SS.h"

TEST(countdown, initial) {
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display());
}

TEST(countdown, set) {
    DDD_HH_MM_SS_set(1, 2, 3, 4);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  1d02h03m04s", DDD_HH_MM_SS_display());
}

TEST(countdown, step) {
    DDD_HH_MM_SS_set(1, 1, 1, 1);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  1d01h01m01s", DDD_HH_MM_SS_display());

    DDD_HH_MM_SS_step(24*60*60);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d01h01m01s", DDD_HH_MM_SS_display());

    DDD_HH_MM_SS_step(60*60);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d00h01m01s", DDD_HH_MM_SS_display());

    DDD_HH_MM_SS_step(60);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d00h00m01s", DDD_HH_MM_SS_display());

    DDD_HH_MM_SS_step(1);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display());

    DDD_HH_MM_SS_step(1);
    DDD_HH_MM_SS_update();
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display());
}
