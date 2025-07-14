#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(single, step) {
	BaseCounter single{12, 7};

#ifdef WHITEBOX_TEST
	ASSERT_EQ(12, single.range_);
	ASSERT_EQ(7, single.value_);
	ASSERT_TRUE(single.next_ == nullptr);
#endif
	ASSERT_EQ(7, single.GetValue());
	single.Step1();
	ASSERT_EQ(6, single.GetValue());
	single.StepN(4);
	ASSERT_EQ(2, single.GetValue());
	single.StepN(3);
	ASSERT_EQ(0, single.GetValue());
	single.Step1();
	ASSERT_EQ(0, single.GetValue());
}
