#include "DDD_HH_MM_SS.h"

#include <stdio.h>

struct DDD_HH_MM_SS_ DDD_HH_MM_SS = {
	{999, 0, NULL },
	{24,  0, &DDD_HH_MM_SS.days_},
	{60,  0, &DDD_HH_MM_SS.hours_},
	{60,  0, &DDD_HH_MM_SS.minutes_},
};

void DDD_HH_MM_SS_update(void) {
	const size_t n_avail = sizeof DDD_HH_MM_SS.display_;
	const size_t n_used = snprintf(DDD_HH_MM_SS.display_, n_avail,
									"%3dd%02dh%02dm%02ds",
									DDD_HH_MM_SS.days_.value_,
									DDD_HH_MM_SS.hours_.value_,
									DDD_HH_MM_SS.minutes_.value_,
									DDD_HH_MM_SS.seconds_.value_);
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

const char* DDD_HH_MM_SS_display() {
	return DDD_HH_MM_SS.display_;
}
