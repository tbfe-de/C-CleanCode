#include "DDD_HH_MM_SS.h"

#include <stdio.h>

void DDD_HH_MM_SS_Init(DDD_HH_MM_SS* self, SBuffer* display) {
	ChainCounter_Init(&self->days_, 999, 0, NULL);
	ChainCounter_Init(&self->hours_, 24, 0, &self->days_);
	ChainCounter_Init(&self->minutes_, 60, 0, &self->hours_);
	ChainCounter_Init(&self->seconds_, 60, 0, &self->minutes_);
	self->display_ = display;
}

void DDD_HH_MM_SS_set(DDD_HH_MM_SS* self, int const d,
					  int const  h, int const m, int const s) {
	self->days_.value_ = d;
	self->hours_.value_ = h;
	self->minutes_.value_ = m;
	self->seconds_.value_ = s;
}

long DDD_HH_MM_SS_remaining(const DDD_HH_MM_SS* self) {
	return ChainCounter_Remaining(&self->seconds_);
}

void DDD_HH_MM_SS_step(DDD_HH_MM_SS* self, int const distance) {
	ChainCounter_StepN(&self->seconds_, distance);
}

void DDD_HH_MM_SS_display(const DDD_HH_MM_SS* self) {
	const size_t n_used = SBprintf(self->display_,
									"%3dd%02dh%02dm%02ds",
									self->days_.value_,
									self->hours_.value_,
									self->minutes_.value_,
									self->seconds_.value_);
}
