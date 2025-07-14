#include "ChainCounter.h"

void ChainCounter_Init(ChainCounter* const self, int const range,
                       int const value, ChainCounter* const next) {
	self->range_ = range;
	self->value_ = value;
	self->next_ = next;
}

int ChainCounter_Step1(ChainCounter* const self) {
	if (self->value_ > 0) {
		--(self->value_);
		return 1;
	}
	if (self->next_ && ChainCounter_Step1(self->next_)) {
		self->value_ = self->range_-1;
		return 1;
	}
	return 0;
}
	
void ChainCounter_StepN(ChainCounter* const self, int distance) {
	for (; distance > 0; --distance)
		ChainCounter_Step1(self);
}
		
int ChainCounter_GetValue(const ChainCounter* const self) {
	return self->value_;
}

long ChainCounter_Remaining(const ChainCounter* const self) {
	long result = self->value_;
	if (self->next_) {
		result += self->range_
                        * ChainCounter_Remaining(self->next_);
	}
	return result;
}
