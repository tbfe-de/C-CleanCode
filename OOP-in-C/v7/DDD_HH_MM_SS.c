#include "DDD_HH_MM_SS.h"

struct DDD_HH_MM_SS_ DDD_HH_MM_SS = {
	{999, 0, NULL },
	{24,  0, &DDD_HH_MM_SS.days_},
	{60,  0, &DDD_HH_MM_SS.hours_},
	{60,  0, &DDD_HH_MM_SS.minutes_},
};

static char chr_digit(const ChainCounter* const counter, const int decimal) {
	const int value = ChainCounter_GetValue(counter);
	return '0' + value / decimal % 10;
}

void DDD_HH_MM_SS_update(void) {
	DDD_HH_MM_SS.display_[0] = chr_digit(&DDD_HH_MM_SS.days_, 100);
	DDD_HH_MM_SS.display_[0] == '0' && (DDD_HH_MM_SS.display_[0] = ' ');
	DDD_HH_MM_SS.display_[1] = chr_digit(&DDD_HH_MM_SS.days_, 10);
	DDD_HH_MM_SS.display_[1] == '0' && (DDD_HH_MM_SS.display_[1] = ' ');
	DDD_HH_MM_SS.display_[2] = chr_digit(&DDD_HH_MM_SS.days_, 1);
	DDD_HH_MM_SS.display_[3] = 'd';
	DDD_HH_MM_SS.display_[4] = chr_digit(&DDD_HH_MM_SS.hours_, 10);
	DDD_HH_MM_SS.display_[5] = chr_digit(&DDD_HH_MM_SS.hours_, 1);
	DDD_HH_MM_SS.display_[6] = 'h';
	DDD_HH_MM_SS.display_[7] = chr_digit(&DDD_HH_MM_SS.minutes_, 10);
	DDD_HH_MM_SS.display_[8] = chr_digit(&DDD_HH_MM_SS.minutes_, 1);
	DDD_HH_MM_SS.display_[9] = 'm';
	DDD_HH_MM_SS.display_[10] = chr_digit(&DDD_HH_MM_SS.seconds_, 10);
	DDD_HH_MM_SS.display_[11] = chr_digit(&DDD_HH_MM_SS.seconds_, 1);
	DDD_HH_MM_SS.display_[12] = 's';
	DDD_HH_MM_SS.display_[13] = '\0';
}

void DDD_HH_MM_SS_set(int const d, int const  h, int const m, int const s) {
	DDD_HH_MM_SS.days_.value_ = d;
	DDD_HH_MM_SS.hours_.value_ = h;
	DDD_HH_MM_SS.minutes_.value_ = m;
	DDD_HH_MM_SS.seconds_.value_ = s;
}

long DDD_HH_MM_SS_remaining() {
	return ChainCounter_Remaining(&DDD_HH_MM_SS.seconds_);
}

void DDD_HH_MM_SS_step(int const distance) {
	ChainCounter_StepN(&DDD_HH_MM_SS.seconds_, distance);
}
