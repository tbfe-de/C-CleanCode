#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(multiple, step) {
	const size_t N = 4;
	ChainCounter arr[N]{
		{2, 1},
		{2, 1, &arr[0]},
		{2, 1, &arr[1]},
		{2, 1, &arr[2]},
	};

	ASSERT_EQ(1, arr[3].GetValue());
	ASSERT_EQ(1, arr[2].GetValue());
	ASSERT_EQ(1, arr[1].GetValue());
	ASSERT_EQ(1, arr[0].GetValue());

	arr[3].Step1();
	ASSERT_EQ(14, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(13, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(12, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(11, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(10, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(9, arr[3].Remaining());

	arr[3].Step1();
	ASSERT_EQ(8, arr[3].Remaining());
	ASSERT_EQ(4, arr[2].Remaining());
	ASSERT_EQ(2, arr[1].Remaining());
	ASSERT_EQ(1, arr[0].Remaining());
	ASSERT_EQ(0, arr[3].GetValue());
	ASSERT_EQ(0, arr[2].GetValue());
	ASSERT_EQ(0, arr[1].GetValue());
	ASSERT_EQ(1, arr[0].GetValue());

	arr[3].StepN(7);
	ASSERT_EQ(1, arr[3].Remaining());
	ASSERT_EQ(0, arr[2].Remaining());
	ASSERT_EQ(0, arr[1].Remaining());
	ASSERT_EQ(0, arr[0].Remaining());
	arr[3].Step1();
	ASSERT_EQ(0, arr[3].Remaining());
	ASSERT_EQ(0, arr[2].Remaining());
	ASSERT_EQ(0, arr[1].Remaining());
	ASSERT_EQ(0, arr[0].Remaining());
	arr[3].Step1();
	ASSERT_EQ(0, arr[3].Remaining());

	arr[3].StepN(7);
	ASSERT_EQ(0, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(0, arr[3].Remaining());
	arr[3].Step1();
	ASSERT_EQ(0, arr[3].Remaining());
}
