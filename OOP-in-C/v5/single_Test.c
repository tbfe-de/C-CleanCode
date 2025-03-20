#include "../gtest/gtest.h"

#include "BaseCounter.h"

TEST(single, step) {
	BaseCounter single;
	BaseCounter_Init(&single, 12, 7);

#ifdef WHITEBOX_TEST
	ASSERT_EQ(12, single.range_);
	ASSERT_EQ(7, single.value_);
	ASSERT_TRUE(single.next_ == NULL);
#endif
	ASSERT_EQ(7, BaseCounter_GetValue(&single));
	BaseCounter_Step1(&single);
	ASSERT_EQ(6, BaseCounter_GetValue(&single));
	BaseCounter_StepN(&single, 4);
	ASSERT_EQ(2, BaseCounter_GetValue(&single));
	BaseCounter_StepN(&single, 3);
	ASSERT_EQ(0, BaseCounter_GetValue(&single));
	BaseCounter_Step1(&single);
	ASSERT_EQ(0, BaseCounter_GetValue(&single));
}
