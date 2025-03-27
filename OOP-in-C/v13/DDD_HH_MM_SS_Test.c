#include "../gtest/gtest.h"

// if more test groups are required define
// TESTCASE-s accordingly in `unit_Test.c`

#include "DDD_HH_MM_SS.h"

TEST(countdown, initial) {
    DDD_HH_MM_SS obj;
    DDD_HH_MM_SS_Init(&obj);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display(&obj));
}

TEST(countdown, set) {
    DDD_HH_MM_SS obj;
    DDD_HH_MM_SS_Init(&obj);
    DDD_HH_MM_SS_set(&obj, 1, 2, 3, 4);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  1d02h03m04s", DDD_HH_MM_SS_display(&obj));
}

TEST(countdown, step) {
    DDD_HH_MM_SS obj;
    DDD_HH_MM_SS_Init(&obj);
    DDD_HH_MM_SS_set(&obj, 1, 1, 1, 1);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  1d01h01m01s", DDD_HH_MM_SS_display(&obj));

    DDD_HH_MM_SS_step(&obj, 24*60*60);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d01h01m01s", DDD_HH_MM_SS_display(&obj));

    DDD_HH_MM_SS_step(&obj, 60*60);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d00h01m01s", DDD_HH_MM_SS_display(&obj));

    DDD_HH_MM_SS_step(&obj, 60);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d00h00m01s", DDD_HH_MM_SS_display(&obj));

    DDD_HH_MM_SS_step(&obj, 1);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display(&obj));

    DDD_HH_MM_SS_step(&obj, 1);
    DDD_HH_MM_SS_update(&obj);
    EXPECT_STREQ("  0d00h00m00s", DDD_HH_MM_SS_display(&obj));
}
