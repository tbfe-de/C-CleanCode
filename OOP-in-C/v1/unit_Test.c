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
	ChainCounter single;
	ChainCounter_Init(&single, 12, 7, NULL);

#ifdef WHITEBOX_TEST
	assert(single.range_ == 12);
	assert(single.value_ == 7);
	assert(single.next_ == NULL);
#endif
	assert(ChainCounter_GetValue(&single) == 7);
	ChainCounter_Step1(&single);
	assert(ChainCounter_GetValue(&single) == 6);
	ChainCounter_StepN(&single, 4);
	assert(ChainCounter_GetValue(&single) == 2);
	ChainCounter_StepN(&single, 3);
	assert(ChainCounter_GetValue(&single) == 0);
	ChainCounter_Step1(&single);
	assert(ChainCounter_GetValue(&single) == 0);
}

void run_twostage(void) {
	ChainCounter c_upper;
	ChainCounter_Init(&c_upper, 4, 3, NULL);
	ChainCounter c_lower;
	ChainCounter_Init(&c_lower, 7, 6, &c_upper);

	assert(ChainCounter_GetValue(&c_upper) == 3);
	assert(ChainCounter_GetValue(&c_lower) == 6);
	ChainCounter_Step1(&c_upper);
	assert(ChainCounter_GetValue(&c_upper) == 2);

	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
/*	assert(ChainCounter_GetValue(&c_upper) == ?...?);
	assert(ChainCounter_GetValue(&c_lower) == ?...?);
*/
	ChainCounter_StepN(&c_lower, 3);
	assert(ChainCounter_GetValue(&c_upper) == 0);
	assert(ChainCounter_GetValue(&c_lower) == 0);
}

/*********************************************************************/

void run_multiple(void) {

	const size_t N = 4;
	ChainCounter arr[N];

	for (int i = 0; i < N; ++i) {
		ChainCounter *const pn = (i > 0) ? &arr[i-1] : NULL;
		ChainCounter_Init(&arr[i], 2, 1, pn);
	}
	assert(ChainCounter_Remaining(&arr[3]) == 15);
	assert(ChainCounter_GetValue(&arr[3]) == 1);
	assert(ChainCounter_GetValue(&arr[2]) == 1);
	assert(ChainCounter_GetValue(&arr[1]) == 1);
	assert(ChainCounter_GetValue(&arr[0]) == 1);

	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 14);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 13);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 12);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 11);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 10);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 9);

	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 8);
	assert(ChainCounter_Remaining(&arr[2]) == 4);
	assert(ChainCounter_Remaining(&arr[1]) == 2);
	assert(ChainCounter_Remaining(&arr[0]) == 1);
	assert(ChainCounter_GetValue(&arr[3]) == 0);
	assert(ChainCounter_GetValue(&arr[2]) == 0);
	assert(ChainCounter_GetValue(&arr[1]) == 0);
	assert(ChainCounter_GetValue(&arr[0]) == 1);

	ChainCounter_StepN(&arr[3], 7);
	assert(ChainCounter_Remaining(&arr[3]) == 1);
	assert(ChainCounter_Remaining(&arr[0]) == 0);
	assert(ChainCounter_Remaining(&arr[1]) == 0);
	assert(ChainCounter_Remaining(&arr[0]) == 0);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 0);
	assert(ChainCounter_Remaining(&arr[2]) == 0);
	assert(ChainCounter_Remaining(&arr[1]) == 0);
	assert(ChainCounter_Remaining(&arr[0]) == 0);
	ChainCounter_Step1(&arr[3]);
	assert(ChainCounter_Remaining(&arr[3]) == 0);
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
