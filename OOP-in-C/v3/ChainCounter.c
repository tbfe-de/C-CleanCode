#include "ChainCounter.h"

ChainCounter::ChainCounter(int const range, int const value,
						   ChainCounter* const next)
	: range_{range}
	, value_{value}
	, next_{next}
{}

bool ChainCounter::Step1() {
	if (value_ > 0) {
		--value_;
		return true;
	}
	if (next_ && next_->Step1()) {
		value_ = range_-1;
		return true;
	}
	return false;
}

void ChainCounter::StepN(int distance) {
	for (; distance > 0; --distance)
		Step1();
}

int ChainCounter::GetValue() const {
	return value_;
}

long ChainCounter::Remaining() const {
	long result = value_;
	if (next_) {
		result += range_
                * next_->Remaining();
	}
	return result;
}

void ChainCounter::operator=(int value) {
	value_ = value;
}
