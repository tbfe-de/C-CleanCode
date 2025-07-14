#include "../gtest/gtest.h"

#include "BaseCounter.h"
#include "c_calls.h"

TEST(single, step) {
	BaseCounter single;
	DCALL_2(BaseCounter, single, Init, 12, 7);

#ifdef WHITEBOX_TEST
	ASSERT_EQ(12, single.range_);
	ASSERT_EQ(7, single.value_);
	ASSERT_TRUE(single.next_ == NULL);
#endif
	ASSERT_EQ(7, DCALL_(BaseCounter, single, GetValue));
	DCALL_(BaseCounter, single, Step1);
	ASSERT_EQ(6, DCALL_(BaseCounter, single, GetValue));
	DCALL_1(BaseCounter, single, StepN, 4);
	ASSERT_EQ(2, DCALL_(BaseCounter, single, GetValue));
	DCALL_1(BaseCounter, single, StepN, 3);
	ASSERT_EQ(0, DCALL_(BaseCounter, single, GetValue));
	DCALL_(BaseCounter, single, Step1);
	ASSERT_EQ(0, DCALL_(BaseCounter, single, GetValue));
}
