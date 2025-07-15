/*
 project specific header files
*/
#include "ChainCounter.h"

/*
 * standard library header files
*/
#include <assert.h>	/* assert (macro) */
#include <stddef.h>	/* NULL (macro) */

/*********************************************************************/

void run_single(void) {
	BaseCounter single;
	BaseCounter_Init(&single, 12, 7);

#ifdef WHITEBOX_TEST
	assert(single.range_ == 12);
	assert(single.value_ == 7);
#endif
	assert(BaseCounter_GetValue(&single) == 7);
	BaseCounter_Step1(&single);
	assert(BaseCounter_GetValue(&single) == 6);
	BaseCounter_StepN(&single, 4);
	assert(BaseCounter_GetValue(&single) == 2);
	BaseCounter_StepN(&single, 3);
	assert(BaseCounter_GetValue(&single) == 0);
	BaseCounter_Step1(&single);
	assert(BaseCounter_GetValue(&single) == 0);
}

void run_twostage(void) {
	BaseCounter c_upper;
	BaseCounter_Init(&c_upper, 4, 3L);
	ChainCounter c_lower;
	ChainCounter_Init(&c_lower, 7, 6, &c_upper);

	assert(BaseCounter_GetValue(&c_upper) == 3);
	assert(ChainCounter_GetValue(&c_lower) == 6);
	BaseCounter_Step1(&c_upper);
	assert(BaseCounter_GetValue(&c_upper) == 2);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 2);
	assert(ChainCounter_GetValue(&c_lower) == 3);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 2);
	assert(ChainCounter_GetValue(&c_lower) == 0);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 1);
	assert(ChainCounter_GetValue(&c_lower) == 4);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 1);
	assert(ChainCounter_GetValue(&c_lower) == 1);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 0);
	assert(ChainCounter_GetValue(&c_lower) == 5);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 0);
	assert(ChainCounter_GetValue(&c_lower) == 2);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 0);
	assert(ChainCounter_GetValue(&c_lower) == 0);

	ChainCounter_StepN(&c_lower, 3);
	assert(BaseCounter_GetValue(&c_upper) == 0);
	assert(ChainCounter_GetValue(&c_lower) == 0);
}

/*********************************************************************/

void run_multiple(void) {

	BaseCounter most_up;
	BaseCounter_Init(&most_up, 2, 1);
	const size_t N = 3;
	ChainCounter arr[N];
	for (int i = 0; i < N; ++i) {
		BaseCounter *const pn = (i > 0)
									? (BaseCounter*)&arr[i-1]
									: &most_up;
		ChainCounter_Init(&arr[i], 2, 1, pn);
	}
	assert(ChainCounter_Remaining(&arr[2]) == 15);
	assert(ChainCounter_GetValue(&arr[2]) == 1);
	assert(ChainCounter_GetValue(&arr[1]) == 1);
	assert(ChainCounter_GetValue(&arr[0]) == 1);
	assert(BaseCounter_GetValue(&most_up) == 1);

	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 14);
	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 13);
	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 12);
	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 11);
	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 10);
	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 9);

	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 8);
	assert(ChainCounter_Remaining(&arr[1]) == 4);
	assert(ChainCounter_Remaining(&arr[0]) == 2);
	assert(BaseCounter_GetValue(&most_up) == 1);
	assert(ChainCounter_GetValue(&arr[1]) == 0);
	assert(ChainCounter_GetValue(&arr[0]) == 0);
	assert(BaseCounter_GetValue(&most_up) == 1);

	ChainCounter_StepN(&arr[2], 7);
	assert(ChainCounter_Remaining(&arr[2]) == 1);
	assert(ChainCounter_Remaining(&arr[1]) == 0);
	assert(ChainCounter_Remaining(&arr[0]) == 0);
	assert(BaseCounter_Remaining(&most_up) == 0);

	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 0);
	assert(ChainCounter_Remaining(&arr[1]) == 0);
	assert(ChainCounter_Remaining(&arr[0]) == 0);

	ChainCounter_Step1(&arr[2]);
	assert(ChainCounter_Remaining(&arr[2]) == 0);
}

/*********************************************************************/

void  unit_tests(void) {
	run_single();
 	run_twostage();
	run_multiple();
}

#include <stdio.h>

int main(void) {
	unit_tests();
	puts("** unit tests passed **");
	return 0;
}