#include "DDD_HH_MM_SS.h"

#include <stdio.h>

void DDD_HH_MM_SS_Init(DDD_HH_MM_SS* self, SBuffer* display) {
	self->seconds_ = 0;
	self->display_ = display;
}

void DDD_HH_MM_SS_set(DDD_HH_MM_SS* self, int const d,
					  int const  h, int const m, int const s) {
	self->seconds_ = (s % 60)
				   + (m % 60) * 60
				   + (h % 24) * 60*60
				   + (d > 0 ? (d % 1000) * 24*60*60 : 0);
}

long DDD_HH_MM_SS_remaining(const DDD_HH_MM_SS* self) {
	return self->seconds_;
}

void DDD_HH_MM_SS_step(DDD_HH_MM_SS* self, int const distance) {
	self->seconds_ =
		(self->seconds_ > distance) ? self->seconds_ - distance : 0;
}

void DDD_HH_MM_SS_display(const DDD_HH_MM_SS* self) {
	const size_t n_used = SBprintf(self->display_,
									"%3dd%02dh%02dm%02ds",
									self->seconds_ / (24*60*60),
									(self->seconds_ / (60*60)) % 24,
									(self->seconds_ / 60) % 60,
									self->seconds_ % 60);
}
