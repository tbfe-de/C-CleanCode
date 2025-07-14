#include "ChainCounter.h"

#include "c_calls.h"

static void ChainCounter_underflow(ChainCounter* const self) {
    if (VCALL_(BaseCounter, self->base_, chained) > 0) {
		DCALL_(BaseCounter, *self->next_, Step1);
		self->base_.value_ = self->base_.range_ - 1;
	}
}

typedef void (*ChainCounter_virtual_underflow_call)(ChainCounter*);
typedef long (*ChainCounter_virtual_chained_call)(const ChainCounter*);

static long ChainCounter_chained(const ChainCounter* const self) {
    return DCALL_(BaseCounter, *self->next_, Remaining);
}

void (*ChainCounter_virtual[BaseCounter_virtual_size])(void) = {
	(void (*)(void)) ChainCounter_underflow,
	(void (*)(void)) ChainCounter_chained,
};

void ChainCounter_Init(ChainCounter* const self, const int range,
                       const int value, BaseCounter* const next) {
	self->base_.vtable_ = &ChainCounter_virtual[0];
	self->base_.range_ = range;
	self->base_.value_ = value;
	self->next_ = next;
}

void ChainCounter_Step1(ChainCounter* const self) {
	DCALL_(BaseCounter, self->base_, Step1);
}

void ChainCounter_StepN(ChainCounter* const self, int const distance) {
	DCALL_1(BaseCounter, self->base_, StepN, distance);
}

int ChainCounter_GetValue(const ChainCounter* const self) {
	return DCALL_(BaseCounter, self->base_, GetValue);
}

long ChainCounter_Remaining(const ChainCounter* const self) {
	return DCALL_(BaseCounter, self->base_, Remaining);
}
