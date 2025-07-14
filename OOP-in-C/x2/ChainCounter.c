#include "ChainCounter.h"

ChainCounter::ChainCounter(int const range, int const value,
						   BaseCounter& next)
	: BaseCounter(range, value)
	, next_{next}
{}

void ChainCounter::underflow() {
    if (chained() > 0) {
		next_.Step1();
		BaseCounter::operator=(range_ - 1);
	}
}

long ChainCounter::chained() const {
    return next_.Remaining();
}
