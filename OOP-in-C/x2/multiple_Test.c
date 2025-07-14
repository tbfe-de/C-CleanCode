#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(multiple, step) {
	BaseCounter top{2, 1};
	const size_t N = 3;
	ChainCounter arr[N]{
		{2, 1, top},
		{2, 1, arr[0]},
		{2, 1, arr[1]},
	};

	ASSERT_EQ(1, arr[2].GetValue());
	ASSERT_EQ(1, arr[1].GetValue());
	ASSERT_EQ(1, arr[0].GetValue());
	ASSERT_EQ(1, top.GetValue());

	arr[2].Step1();
	ASSERT_EQ(14, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(13, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(12, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(11, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(10, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(9, arr[2].Remaining());

	arr[2].Step1();
	ASSERT_EQ(8, arr[2].Remaining());
	ASSERT_EQ(4, arr[1].Remaining());
	ASSERT_EQ(2, arr[0].Remaining());
	ASSERT_EQ(1, top.Remaining());
	ASSERT_EQ(0, arr[2].GetValue());
	ASSERT_EQ(0, arr[1].GetValue());
	ASSERT_EQ(0, arr[0].GetValue());
	ASSERT_EQ(1, top.GetValue());

	arr[2].StepN(7);
	ASSERT_EQ(1, arr[2].Remaining());
	ASSERT_EQ(0, arr[1].Remaining());
	ASSERT_EQ(0, arr[0].Remaining());
	ASSERT_EQ(0, top.Remaining());
	arr[2].Step1();
	ASSERT_EQ(0, arr[2].Remaining());
	ASSERT_EQ(0, arr[1].Remaining());
	ASSERT_EQ(0, arr[0].Remaining());
	ASSERT_EQ(0, top.Remaining());
	arr[2].Step1();
	ASSERT_EQ(0, arr[2].Remaining());

	arr[2].StepN(7);
	ASSERT_EQ(0, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(0, arr[2].Remaining());
	arr[2].Step1();
	ASSERT_EQ(0, arr[2].Remaining());
}
