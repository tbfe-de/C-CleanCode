#include "run_app.h"

#include "DDD_HH_MM_SS.h"

#include <stdio.h> /* printf() */
#include <stdlib.h> /* rand() */

void run_app(const RDHMS params) {
	DDD_HH_MM_SS_set(params.days_,
					 params.hours_,
					 params.minutes_,
					 params.seconds_);
	long remaining = DDD_HH_MM_SS_remaining();
	unsigned int distance;
	do {
		DDD_HH_MM_SS_update();
		distance = 1 + rand() % params.rlimit_;
		if (distance > remaining) distance = remaining;
		(void) printf("%s -- next: %4u steps of %ld remaining\n",
					   DDD_HH_MM_SS_display(), distance, remaining);
		DDD_HH_MM_SS_step(distance);
		remaining = DDD_HH_MM_SS_remaining();
	} while (remaining > 0);
	DDD_HH_MM_SS_update();
	(void) printf("%s -- DONE\n", DDD_HH_MM_SS.display_);
}
