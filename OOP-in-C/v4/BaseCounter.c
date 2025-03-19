#include "BaseCounter.h"

BaseCounter::BaseCounter(int const range, int const value)
	: range_{range}
	, value_{value}
{}

void BaseCounter::underflow() {
    /*empty*/
}

long BaseCounter::chained() const {
    return 0L;
}

void BaseCounter::Step1() {
	if (value_ == 0)
		underflow();
	else
		--value_;
}

void BaseCounter::StepN(int distance) {
	for (; distance > 0; --distance)
		Step1();
}

int BaseCounter::GetValue() const {
	return value_;
}

long BaseCounter::Remaining() const {
    return value_
         + chained() * range_;
}

void BaseCounter::operator=(int value) {
	value_ = value;
}
