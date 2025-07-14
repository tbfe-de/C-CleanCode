#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(twostage, step) {
	BaseCounter c_upper{4, 3};
	ChainCounter c_lower{7, 6, c_upper};

	ASSERT_EQ(3, c_upper.GetValue());
	ASSERT_EQ(6, c_lower.GetValue());
	c_upper.Step1();
	ASSERT_EQ(2, c_upper.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(2, c_upper.GetValue());
	ASSERT_EQ(3, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(2, c_upper.GetValue());
	ASSERT_EQ(0, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(1, c_upper.GetValue());
	ASSERT_EQ(4, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(1, c_upper.GetValue());
	ASSERT_EQ(1, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(0, c_upper.GetValue());
	ASSERT_EQ(5, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(0, c_upper.GetValue());
	ASSERT_EQ(2, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(0, c_upper.GetValue());
	ASSERT_EQ(0, c_lower.GetValue());

	c_lower.StepN(3);
	ASSERT_EQ(0, c_upper.GetValue());
	ASSERT_EQ(0, c_lower.GetValue());
}
