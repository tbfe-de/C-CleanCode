#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(single, step) {
	ChainCounter single;	
	ChainCounter_Init(&single, 12, 7, NULL);

#ifdef WHITEBOX_TEST
	ASSERT_EQ(12, single.range_);
	ASSERT_EQ(7, single.value_);
	ASSERT_TRUE(single.next_ == NULL);
#endif
	ASSERT_EQ(7, ChainCounter_GetValue(&single));
	ChainCounter_Step1(&single);
	ASSERT_EQ(6, ChainCounter_GetValue(&single));
	ChainCounter_StepN(&single, 4);
	ASSERT_EQ(2, ChainCounter_GetValue(&single));
	ChainCounter_StepN(&single, 3);
	ASSERT_EQ(0, ChainCounter_GetValue(&single));
	ChainCounter_Step1(&single);
	ASSERT_EQ(0, ChainCounter_GetValue(&single));
}

