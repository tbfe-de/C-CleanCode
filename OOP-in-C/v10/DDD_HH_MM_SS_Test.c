#include "../gtest/gtest.h"

// if more test groups are required define
// TESTCASE-s accordingly in `unit_Test.c`

#include "DDD_HH_MM_SS.h"

#include "SBuffer.h"

char buffer[200];
SBuffer result = SBuffer_INIT(buffer);

TEST(countdown, initial) {
    DDD_HH_MM_SS obj;
    SBclear(&result);
    DDD_HH_MM_SS_Init(&obj, &result);
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  0d00h00m00s", result.static_buffer);
}

TEST(countdown, set) {
    DDD_HH_MM_SS obj;
    SBclear(&result);
    DDD_HH_MM_SS_Init(&obj, &result);
    DDD_HH_MM_SS_set(&obj, 1, 2, 3, 4);
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d02h03m04s", result.static_buffer);
}

TEST(countdown, step) {
    DDD_HH_MM_SS obj;
    DDD_HH_MM_SS_Init(&obj, &result);
    DDD_HH_MM_SS_set(&obj, 1, 1, 1, 1);
    SBclear(&result);
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s", result.static_buffer);

    DDD_HH_MM_SS_step(&obj, 24*60*60);
    /* Note: result not cleared here, instead adding a newline! */
    SBprintf(&result, "\n");
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s\n"
                 "  0d01h01m01s", result.static_buffer);

    DDD_HH_MM_SS_step(&obj, 60*60);
    SBprintf(&result, "\n");
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s\n"
                 "  0d01h01m01s\n"
                 "  0d00h01m01s", result.static_buffer);

    DDD_HH_MM_SS_step(&obj, 60);
    SBprintf(&result, "\n");
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s\n"
                 "  0d01h01m01s\n"
                 "  0d00h01m01s\n"
                 "  0d00h00m01s", result.static_buffer);

    DDD_HH_MM_SS_step(&obj, 1);
    SBprintf(&result, "\n");
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s\n"
                 "  0d01h01m01s\n"
                 "  0d00h01m01s\n"
                 "  0d00h00m01s\n"
                 "  0d00h00m00s", result.static_buffer);

    DDD_HH_MM_SS_step(&obj, 1);
    SBprintf(&result, "\n");
    DDD_HH_MM_SS_display(&obj);
    EXPECT_STREQ("  1d01h01m01s\n"
                 "  0d01h01m01s\n"
                 "  0d00h01m01s\n"
                 "  0d00h00m01s\n"
                 "  0d00h00m00s\n"
                 "  0d00h00m00s", result.static_buffer);
}
