#include "BaseCounter.h"
#include "ChainCounter.h"

struct {
	BaseCounter days_;
	ChainCounter hours_;
	ChainCounter minutes_;
	ChainCounter seconds_;
	char display_[14];
} DDD_HH_MM_SS = {
	{BaseCounter_virtual, 999, 0},
	{{ChainCounter_virtual, 24, 0}, &DDD_HH_MM_SS.days_},
	{{ChainCounter_virtual, 60, 0}, &DDD_HH_MM_SS.hours_.base_},
	{{ChainCounter_virtual, 60, 0}, &DDD_HH_MM_SS.minutes_.base_},
};

static char chr_digit(const BaseCounter* const counter, const int decimal) {
	const int value = BaseCounter_GetValue(counter);
	return '0' + value / decimal % 10;
}
static void DDD_HH_MM_SS_update() {
	DDD_HH_MM_SS.display_[0] = chr_digit(&DDD_HH_MM_SS.days_, 100);
	DDD_HH_MM_SS.display_[0] == '0' && (DDD_HH_MM_SS.display_[0] = ' ');
	DDD_HH_MM_SS.display_[1] = chr_digit(&DDD_HH_MM_SS.days_, 10);
	DDD_HH_MM_SS.display_[1] == '0' && (DDD_HH_MM_SS.display_[1] = ' ');
	DDD_HH_MM_SS.display_[2] = chr_digit(&DDD_HH_MM_SS.days_, 1);
	DDD_HH_MM_SS.display_[3] = 'd';
	DDD_HH_MM_SS.display_[4] = chr_digit(&DDD_HH_MM_SS.hours_.base_, 10);
	DDD_HH_MM_SS.display_[5] = chr_digit(&DDD_HH_MM_SS.hours_.base_, 1);
	DDD_HH_MM_SS.display_[6] = 'h';
	DDD_HH_MM_SS.display_[7] = chr_digit(&DDD_HH_MM_SS.minutes_.base_, 10);
	DDD_HH_MM_SS.display_[8] = chr_digit(&DDD_HH_MM_SS.minutes_.base_, 1);
	DDD_HH_MM_SS.display_[9] = 'm';
	DDD_HH_MM_SS.display_[10] = chr_digit(&DDD_HH_MM_SS.seconds_.base_, 10);
	DDD_HH_MM_SS.display_[11] = chr_digit(&DDD_HH_MM_SS.seconds_.base_, 1);
	DDD_HH_MM_SS.display_[12] = 's';
	DDD_HH_MM_SS.display_[13] = '\0';
}

void DDD_HH_MM_SS_set(int const d, int const  h, int const m, int const s) {
	DDD_HH_MM_SS.days_.value_ = d;
	DDD_HH_MM_SS.hours_.base_.value_ = h;
	DDD_HH_MM_SS.minutes_.base_.value_ = m;
	DDD_HH_MM_SS.seconds_.base_.value_ = s;
}

long DDD_HH_MM_SS_remaining() {
	return ChainCounter_Remaining(&DDD_HH_MM_SS.seconds_);
}

void DDD_HH_MM_SS_step(int const distance) {
	ChainCounter_StepN(&DDD_HH_MM_SS.seconds_, distance);
}

#include <stdio.h> /* printf (function) */
#include <stdlib.h> /* rand (function) */

void run_app(int days, int hours, int minutes, int seconds) {
	DDD_HH_MM_SS_set(days, hours, minutes, seconds);
	long remaining = DDD_HH_MM_SS_remaining();
	unsigned int distance;
	do {
		DDD_HH_MM_SS_update();
		distance = 1 + rand() % (10*1000);
		if (distance > remaining) distance = remaining;
		(void) printf("%s -- next: %4u steps of %ld remaining\n",
					   DDD_HH_MM_SS.display_, distance, remaining);
		DDD_HH_MM_SS_step(distance);
		remaining = DDD_HH_MM_SS_remaining();
	} while (remaining > 0);
	DDD_HH_MM_SS_update();
	(void) printf("%s -- DONE\n", DDD_HH_MM_SS.display_);
}