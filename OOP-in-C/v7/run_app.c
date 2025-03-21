#include "ChainCounter.h"

#include <stdio.h> /* printf() */
#include <stdlib.h> /* rand() */

extern struct {
	ChainCounter days_;
	ChainCounter hours_;
	ChainCounter minutes_;
	ChainCounter seconds_;
	char display_[14];
} DDD_HH_MM_SS;

extern void DDD_HH_MM_SS_set();
extern void DDD_HH_MM_SS_update();
extern void DDD_HH_MM_SS_step();
extern long DDD_HH_MM_SS_remaining();

void run_app(int days, int hours, int minutes, int seconds) {
	DDD_HH_MM_SS_set(days, hours, minutes, seconds);
	long remaining = DDD_HH_MM_SS_remaining();
	unsigned int distance;
	do {
		DDD_HH_MM_SS_update();
		distance = rand() % (10*1000);
		if (distance > remaining) distance = remaining;
		(void) printf("%s -- next: %4u steps of %ld remaining\n",
					   DDD_HH_MM_SS.display_, distance, remaining);
		DDD_HH_MM_SS_step(distance);
		remaining = DDD_HH_MM_SS_remaining();
	} while (remaining > 0);
	DDD_HH_MM_SS_update();
	(void) printf("%s -- DONE\n", DDD_HH_MM_SS.display_);
}
