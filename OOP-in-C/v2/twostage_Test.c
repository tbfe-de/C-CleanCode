#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(twostage, step) {
	ChainCounter c_upper;
	ChainCounter_Init(&c_upper, 4, 3, NULL);
	ChainCounter c_lower;
	ChainCounter_Init(&c_lower, 7, 6, &c_upper);

	ASSERT_EQ(3, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(6, ChainCounter_GetValue(&c_lower));
	ChainCounter_Step1(&c_upper);
	ASSERT_EQ(2, ChainCounter_GetValue(&c_upper));
	
	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(2, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(3, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(2 ,ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(0 ,ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(1, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(4, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(1, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(1, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(0, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(5, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(0, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(2, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(0, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(0, ChainCounter_GetValue(&c_lower));

	ChainCounter_StepN(&c_lower, 3);
	ASSERT_EQ(0, ChainCounter_GetValue(&c_upper));
	ASSERT_EQ(0, ChainCounter_GetValue(&c_lower));
}
