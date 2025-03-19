#include "../gtest/gtest.h"

#include "ChainCounter.h"

TEST(multiple, step) {
	const size_t N = 4;
	ChainCounter arr[N];

	for (int i = 0; i < N; ++i) {
		ChainCounter *const pn = (i > 0) ? &arr[i-1] : NULL;
		ChainCounter_Init(&arr[i], 2, 1, pn);
	}
	ASSERT_EQ(15, ChainCounter_Remaining(&arr[3]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[3]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[2]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[1]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[0]));

	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(14, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(13, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(12, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(11, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(10, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(9, ChainCounter_Remaining(&arr[3]));

	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(8, ChainCounter_Remaining(&arr[3]));
	ASSERT_EQ(4, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(2, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(1, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[3]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[2]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[1]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[0]));

	ChainCounter_StepN(&arr[3], 7);
	ASSERT_EQ(1, ChainCounter_Remaining(&arr[3]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[3]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[3]));

	ChainCounter_StepN(&arr[3], 7);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[3]));
	ChainCounter_Step1(&arr[3]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[3]));
}
