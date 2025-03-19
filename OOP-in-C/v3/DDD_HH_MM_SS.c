#include "ChainCounter.h"

class DDD_HH_MM_SS {
	static ChainCounter days_;
	static ChainCounter hours_;
	static ChainCounter minutes_;
	static ChainCounter seconds_;
	static char chr_digit(const ChainCounter&, int);
	static char display_[14];
public:
	static void set(int, int, int, int);
	static void update();
	static void step(int);
	static long remaining();
	static const char* get();
};
ChainCounter DDD_HH_MM_SS::days_{999, 0 };
ChainCounter DDD_HH_MM_SS::hours_{24, 0, &DDD_HH_MM_SS::days_};
ChainCounter DDD_HH_MM_SS::minutes_{60, 0, &DDD_HH_MM_SS::hours_};
ChainCounter DDD_HH_MM_SS::seconds_{60, 0, &DDD_HH_MM_SS::minutes_};
char DDD_HH_MM_SS::display_[14];

char DDD_HH_MM_SS::chr_digit(const ChainCounter& counter,
									const int decimal) {
	const int value = counter.GetValue();
	return '0' + value / decimal % 10;
}

void DDD_HH_MM_SS::update() {
	display_[0] = chr_digit(DDD_HH_MM_SS::days_, 100);
	display_[0] == '0' && (DDD_HH_MM_SS::display_[0] = ' ');
	display_[1] = chr_digit(DDD_HH_MM_SS::days_, 10);
	display_[1] == '0' && (DDD_HH_MM_SS::display_[1] = ' ');
	display_[2] = chr_digit(DDD_HH_MM_SS::days_, 1);
	display_[3] = 'd';
	display_[4] = chr_digit(DDD_HH_MM_SS::hours_, 10);
	display_[5] = chr_digit(DDD_HH_MM_SS::hours_, 1);
	display_[6] = 'h';
	display_[7] = chr_digit(DDD_HH_MM_SS::minutes_, 10);
	display_[8] = chr_digit(DDD_HH_MM_SS::minutes_, 1);
	display_[9] = 'm';
	display_[10] = chr_digit(DDD_HH_MM_SS::seconds_, 10);
	display_[11] = chr_digit(DDD_HH_MM_SS::seconds_, 1);
	display_[12] = 's';
	display_[13] = '\0';
}

void DDD_HH_MM_SS::set(int const d, int const  h, int const m, int const s) {
	days_ = d;
	hours_ = h;
	minutes_ = m;
	seconds_ = s;
}

const char* DDD_HH_MM_SS::get() {
	return display_;
}

long DDD_HH_MM_SS::remaining() {
	return DDD_HH_MM_SS::seconds_.Remaining();
}

void DDD_HH_MM_SS::step(int const distance) {
	seconds_.StepN(distance);
}

#include <stdio.h> /* printf (function) */
#include <stdlib.h> /* rand (function) */

void run_app(int days, int hours, int minutes, int seconds) {
	DDD_HH_MM_SS::set(days, hours, minutes, seconds);
	long remaining = DDD_HH_MM_SS::remaining();
	unsigned int distance;
	do {
		DDD_HH_MM_SS::update();
		distance = rand() % (10*1000);
		if (distance > remaining) distance = remaining;
		printf("%s -- next: %4u steps of %ld remaining\n",
			DDD_HH_MM_SS::get(), distance, remaining);
		DDD_HH_MM_SS::step(distance);
		remaining = DDD_HH_MM_SS::remaining();
	} while (remaining > 0);
	DDD_HH_MM_SS::update();
	printf("%s -- DONE\n", DDD_HH_MM_SS::get());
}

int main(int argc, char* argv[]) {
	run_app((argc > 1) ? atoi(argv[1]) : 4,
			(argc > 2) ? atoi(argv[2]) : 3,
			(argc > 3) ? atoi(argv[3]) : 2,
			(argc > 4) ? atoi(argv[4]) : 1);
}
