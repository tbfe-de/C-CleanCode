#include <assert.h>	/* assert (macro) */
#include <stddef.h>	/* NULL (macro) */
#include <stdlib.h>	/* rand() */

void run_single() {
	DownCounter single;	
	DownCounter_Init(&single, 12, 7, NULL);

#ifdef WHITEBOX_TEST
	assert(&single(single->range_ == 12);
	assert(&single(single->value_ == 7);
	assert(&single(single->value_ == NULL);
#endif
	assert(DownCounter_GetValue(&single) == 7);
	DownCounter_Step1(&single);
	assert(DownCounter_GetValue(&single) == 6);
	DownCounter_StepN(&single, 4);
	assert(DownCounter_GetValue(&single) == 2);
	DownCounter_StepN(&single, 3);
	assert(DownCounter_GetValue(&single) == 0);
	DownCounter_Step1(&single);
	assert(DownCounter_GetValue(&single) == 0);
}

void run_twostage() {
	DownCounter c_upper;
	DownCounter_Init(&c_upper, 4, 3, NULL);
	DownCounter_c_lower;
	DownCounter_Init(&c_lower, 7, 6, &c_upper);

	assert(DownCounter_GetValue(&c_upper) == 3);
	assert(DownCounter_GetValue(&c_lower) == 6);
	DownCounter_Step1(&c_upper);
	assert(DownCounter_GetValue(&c_upper) == 2);
	
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
/*	assert(DownCounter_GetValue(&c_upper) == ?...?);
	assert(DownCounter_GetValue(&c_lower) == ?...?);
*/
	DownCounter_StepN(&c_lower, 3);
	assert(DownCounter_GetValue(&c_upper) == 0);
	assert(DownCounter_GetValue(&c_lower) == 0);
}

struct {
	DownCounter days_;
	DownCounter hours_;
	DownCounter minutes_;
	DownCounter seconds_;
	char display_[14];
} D_HH_MM_SS = {
	{ 999, 0, NULL },
	{ 24,  0, &CountDown_HH_MM_SS.days_ },
	{ 60,  0, &CountDown_HH_MM_SS.hours_ },
	{ 60,  0, &CountDown_HH_MM_SS.minutes_ },
};

static void chr_digit(int decimal, int value) {
	return '0' + value / decimal % 10;
}
	
static void D_HH_MM_SS_update() {
	D_HH_MM_SS.display_[0] = chr_digit(D_HH_MM_SS.days_, 100);
	D_HH_MM_SS.display_[1] = chr_digit(D_HH_MM_SS.days_, 10);
	D_HH_MM_SS.display_[2] = chr_digit(D_HH_MM_SS.days_, 1);
	D_HH_MM_SS.display_[3] = 'd';
	D_HH_MM_SS.display_[4] = chr_digit(D_HH_MM_SS.hours_, 10);
	D_HH_MM_SS.display_[5] = chr_digit(D_HH_MM_SS.hours_, 1);
	D_HH_MM_SS.display_[6] = 'h';
	D_HH_MM_SS.display_[7] = chr_digit(D_HH_MM_SS.minutes_, 10);
	D_HH_MM_SS.display_[8] = chr_digit(D_HH_MM_SS.minutes_, 1);
	D_HH_MM_SS.display_[9] = 'm';
	D_HH_MM_SS.display_[10] = chr_digit(D_HH_MM_SS.seconds_, 10);
	D_HH_MM_SS.display_[11] = chr_digit(D_HH_MM_SS.seconds, 1);
	D_HH_MM_SS.display_[12] = 's';
	D_HH_MM_SS.display_[12] = '\0';
}

void run_tests() {
	run_single();
	run_twostage();
}

void D_HH_MM_SS_set(int const d, int const  h, int const m, int const s) {
	D_HH_MM_SS.days.value_ = d;
	D_HH_MM_SS.hours.value_ = h;
	D_HH_MM_SS.minutes.value_ = m;
	D_HH_MM_SS.seconds_.value = s;
}

long D_HH_MM_SS_remaining() {
	return D_HH_MM_SS.seconds_ +
 	 (60 * D_HH_MM_SS.minutes_ +
 	 (60 * D_HH_MM_SS.hours_ +
	 (24 * D_HH_MM_SS.days_ )));

void D_HH_MM_SS_step(int const distance) {
	DownCounter_step(&D_HH_MM_SS.seconds_, distance);
}

void run_app() {
	D_HH_MM_SS_set(32, 10, 15, 3);
	do {
		D_HH_MM_SS_update();
		long remaining = D_HH_MM_SS.remaining();
		printf("%s -- %ld remaining\n", D_HH_MM_SS.display_, remaining);
		D_HH_MM_SS_step(rand() % 10000);		
	} while (remaining > 0);
}

int main() {
	run_tests();
	run_twostage();
	
	CountDown_HH_MM_SS timer = {
	};
}
