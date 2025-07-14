#include "../gtest/gtest.h"

#include "BaseCounter.h"
#include "ChainCounter.h"

TEST(multiple, step) {
	BaseCounter top;
	BaseCounter_Init(&top, 2, 1);
	BaseCounter* pn = &top;
	const size_t N = 3;
	ChainCounter arr[N];
	for (int i = 0; i < N; ++i) {
		ChainCounter_Init(&arr[i], 2, 1, pn);
		pn = (BaseCounter*)&arr[i];
	}

	ASSERT_EQ(15, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[2]));
	ASSERT_EQ(1, ChainCounter_GetValue(&arr[1]));
	ASSERT_EQ(1, BaseCounter_GetValue(&top));

	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(14, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(13, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(12, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(11, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(10, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(9, ChainCounter_Remaining(&arr[2]));

	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(8, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(4, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(2, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(1, BaseCounter_Remaining(&top));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[2]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[1]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[0]));
	ASSERT_EQ(1, BaseCounter_GetValue(&top));

	ChainCounter_StepN(&arr[2], 7);
	ASSERT_EQ(1, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, BaseCounter_Remaining(&top));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, BaseCounter_Remaining(&top));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));

	ChainCounter_StepN(&arr[2], 7);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[1]));
	ASSERT_EQ(0, ChainCounter_GetValue(&arr[0]));
	ASSERT_EQ(0, BaseCounter_GetValue(&top));

	ChainCounter_StepN(&arr[2], 6);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, BaseCounter_Remaining(&top));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[1]));
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[0]));
	ASSERT_EQ(0, BaseCounter_Remaining(&top));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));

	ChainCounter_StepN(&arr[2], 7);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
	ChainCounter_Step1(&arr[2]);
	ASSERT_EQ(0, ChainCounter_Remaining(&arr[2]));
}
