#include "../gtest/gtest.h"

#include "run_app.h"

TEST(run_app, run) {
    APP app;
    APP_Init(&app);
    RDHMS params = {0, 0, 0, 0, 0};
#ifdef WHITEBOX_TEST
	ASSERT_EQ(0, app.countdown_.days_.value_);
	ASSERT_EQ(0, app.countdown_.hours_.value_);
	ASSERT_EQ(0, app.countdown_.minutes_.value_);
	ASSERT_EQ(0, app.countdown_.seconds_.value_);
#endif
    // too early to do unit tests as output is
    // always created on the terminal, where it
    // can only be compared vs. expectation by
    // the human user
    //
    // RDHMS params = {1, 0, 0, 0, 1};
    // APP_run(&app, params);
}
