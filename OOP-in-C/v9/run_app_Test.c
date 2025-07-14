#include "../gtest/gtest.h"

#include "run_app.h"

TEST(run_app, run) {
    APP app;
    APP_Init(&app);
    RDHMS params = {1, 0, 0, 0, 3};
#ifdef WHITEBOX_TEST
	ASSERT_EQ(1, app.countdown_.rlimit_);
	ASSERT_EQ(0, app.countdown_.days_.value_);
	ASSERT_EQ(0, app.countdown_.hours_.value_);
	ASSERT_EQ(0, app.countdown_.minutes_.value_);
	ASSERT_EQ(3, app.countdown_.seconds_.value_);
#endif
    char sufficient[200] = {'\0'};
    SBuffer output = SBuffer_INIT(sufficient);
    APP_run(&app, params, &output);
    EXPECT_STREQ("  0d00h00m03s -- next:    1 steps of 3 remaining\n"
                 "  0d00h00m02s -- next:    1 steps of 2 remaining\n"
                 "  0d00h00m01s -- next:    1 steps of 1 remaining\n"
                 "  0d00h00m00s -- DONE\n", output.static_buffer);
}
