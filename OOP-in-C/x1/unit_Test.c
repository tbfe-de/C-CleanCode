/*
 project specific header files
*/
#include "ChainCounter.h"

/*
 * standard library header files
*/
#include <cassert>	/* assert (macro) */

/*********************************************************************/

void run_single(void) {
	ChainCounter single{12 ,7};

#ifdef WHITEBOX_TEST
	assert(single.range_ == 12);
	assert(single.value_ == 7);
	assert(single.next_ == NULL);
#endif
	assert(single.GetValue() == 7);
	single.Step1();
	assert(single.GetValue() == 6);
	single.StepN(4);
	assert(single.GetValue() == 2);
	single.StepN(3);
	assert(single.GetValue() == 0);
	single.Step1();
	assert(single.GetValue() == 0);
}


void run_twostage(void) {
	ChainCounter c_upper{4, 3};
	ChainCounter c_lower{7, 6, &c_upper};

	assert(c_upper.GetValue() == 3);
	assert(c_lower.GetValue() == 6);
	c_upper.Step1();
	assert(c_upper.GetValue() == 2);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 2);
	assert(c_lower.GetValue() == 3);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 2);
	assert(c_lower.GetValue() == 0);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 1);
	assert(c_lower.GetValue() == 4);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 1);
	assert(c_lower.GetValue() == 1);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 0);
	assert(c_lower.GetValue() == 5);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 0);
	assert(c_lower.GetValue() == 2);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 0);
	assert(c_lower.GetValue() == 0);

	c_lower.StepN(3);
	assert(c_upper.GetValue() == 0);
	assert(c_lower.GetValue() == 0);
}

/*********************************************************************/

#if 0
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
#endif
/*********************************************************************/

void  unit_tests(void) {
	run_single();
 	run_twostage();
// run_multiple();
}

#include <iostream>

int main() {
	unit_tests();
	std::cout << "** unit tests passed **" << std::endl;
}
