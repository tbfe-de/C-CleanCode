#include "../gtest/gtest.h"

#include "ChainCounter.h"
#include "c_calls.h"

TEST(twostage, step) {
	BaseCounter c_upper;
	DCALL_2(BaseCounter, c_upper, Init, 4, 3);
	ChainCounter c_lower;
	DCALL_3(ChainCounter, c_lower, Init, 7, 6, &c_upper);

	ASSERT_EQ(3, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(6, DCALL_(ChainCounter, c_lower, GetValue));
	DCALL_(BaseCounter, c_upper, Step1);
	ASSERT_EQ(2, DCALL_(BaseCounter, c_upper, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(2, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(3, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(2, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(0, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(1, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(4, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(1, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(1, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(0, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(5, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(0, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(2, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(0, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(0, DCALL_(ChainCounter, c_lower, GetValue));

	DCALL_1(ChainCounter, c_lower, StepN, 3);
	ASSERT_EQ(0, DCALL_(BaseCounter, c_upper, GetValue));
	ASSERT_EQ(0, ChainCounter_GetValue(&c_lower));
}
