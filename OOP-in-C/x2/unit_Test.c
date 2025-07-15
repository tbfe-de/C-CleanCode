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
	BaseCounter single{12 ,7};

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
	BaseCounter c_upper{4, 3};
	ChainCounter c_lower{7, 6, c_upper};

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

void run_multiple(void) {

	BaseCounter most_up{2, 1};
	const size_t N = 3;
	ChainCounter arr[N] = {
		ChainCounter{2, 1, most_up},
		ChainCounter{2, 1, arr[0]},
		ChainCounter{2, 1, arr[1]}	
	};

	assert(arr[2].Remaining() == 15);
	assert(arr[2].GetValue() == 1);
	assert(arr[1].GetValue() == 1);
	assert(arr[0].GetValue() == 1);
	assert(most_up.GetValue() == 1);

	arr[2].Step1();
	assert(arr[2].Remaining() == 14);
	arr[2].Step1();
	assert(arr[2].Remaining() == 13);
	arr[2].Step1();
	assert(arr[2].Remaining() == 12);
	arr[2].Step1();
	assert(arr[2].Remaining() == 11);
	arr[2].Step1();
	assert(arr[2].Remaining() == 10);
	arr[2].Step1();
	assert(arr[2].Remaining() == 9);

	arr[2].Step1();
	assert(arr[2].Remaining() == 8);
	assert(arr[1].Remaining() == 4);
	assert(arr[0].Remaining() == 2);
	assert(most_up.Remaining() == 1);
	assert(arr[2].GetValue() == 0);
	assert(arr[1].GetValue() == 0);
	assert(arr[0].GetValue() == 0);
	assert(most_up.GetValue() == 1);

	arr[2].StepN(7);
	assert(arr[2].Remaining() == 1);
	assert(most_up.Remaining() == 0);
	assert(arr[0].Remaining() == 0);
	assert(most_up.Remaining() == 0);
	arr[2].Step1();
	assert(arr[2].Remaining() == 0);
	assert(arr[1].Remaining() == 0);
	assert(arr[0].Remaining() == 0);
	assert(most_up.Remaining() == 0);
	arr[2].Step1();
	assert(arr[2].Remaining() == 0);

}
/*********************************************************************/

void  unit_tests(void) {
	run_single();
 	run_twostage();
	run_multiple();
}

#include <iostream>

int main() {
	unit_tests();
	std::cout << "** unit tests passed **" << std::endl;
}
