#include "run_app.h"

#include "DDD_HH_MM_SS.h"

#include <stdio.h> /* printf() */
#include <stdlib.h> /* rand() */

void APP_Init(APP* self) {
	DDD_HH_MM_SS_Init(&self->countdown_);
}

void APP_run(APP* self, const RDHMS params, SBuffer* out) {
	DDD_HH_MM_SS_Init(&self->countdown_);
	DDD_HH_MM_SS_set(&self->countdown_,
					 params.days_,
					 params.hours_,
					 params.minutes_,
					 params.seconds_);
	long remaining = DDD_HH_MM_SS_remaining(&self->countdown_);
	unsigned int distance;
	do {
		DDD_HH_MM_SS_update(&self->countdown_);
		distance = 1 + rand() % params.rlimit_;
		if (distance > remaining) distance = remaining;
		(void) SBprintf(out, "%s -- next: %4u steps of %ld remaining\n",
					   		 DDD_HH_MM_SS_display(&self->countdown_),
					   		 distance, remaining);
		DDD_HH_MM_SS_step(&self->countdown_, distance);
		remaining = DDD_HH_MM_SS_remaining(&self->countdown_);
	} while (remaining > 0);
	DDD_HH_MM_SS_update(&self->countdown_);
	(void) SBprintf(out, "%s -- DONE\n",
				   		 DDD_HH_MM_SS_display(&self->countdown_));
}
