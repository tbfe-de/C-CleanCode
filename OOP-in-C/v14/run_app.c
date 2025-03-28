#include "run_app.h"

#include "DDD_HH_MM_SS.h"

#include <stdio.h> /* printf() */
#include <stdlib.h> /* rand() */

void APP_Init(APP* self, SBuffer* output) {
	DDD_HH_MM_SS_Init(&self->countdown_, output);
	self->output_ = output;
}

void APP_run(APP* self, const RDHMS params) {
	DDD_HH_MM_SS_set(&self->countdown_,
					 params.days_,
					 params.hours_,
					 params.minutes_,
					 params.seconds_);
	long remaining = DDD_HH_MM_SS_remaining(&self->countdown_);
	unsigned int distance;
	do {
		distance = 1 + rand() % params.rlimit_;
		if (distance > remaining) distance = remaining;
		DDD_HH_MM_SS_display(&self->countdown_);
		(void) SBprintf(self->output_, " -- next: %4u steps of %ld remaining\n",
					   			 distance, remaining);
		DDD_HH_MM_SS_step(&self->countdown_, distance);
		remaining = DDD_HH_MM_SS_remaining(&self->countdown_);
	} while (remaining > 0);
	DDD_HH_MM_SS_display(&self->countdown_);
	(void) SBprintf(self->output_, " -- DONE\n");
}
