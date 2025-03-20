#include "ChainCounter.h"

static void ChainCounter_underflow(ChainCounter* const self) {
    if (((BaseCounter_virtual_chained_call)
		 self->base_.vtable_[BaseCounter_virtual_chained])(&self->base_) > 0) {
		BaseCounter_Step1(self->next_);
		self->base_.value_ = self->base_.range_ - 1;
	}
}

static long ChainCounter_chained(const ChainCounter* const self) {
    return BaseCounter_Remaining(self->next_);
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
	BaseCounter_Step1(&self->base_);
}

void ChainCounter_StepN(ChainCounter* const self, int const distance) {
	BaseCounter_StepN(&self->base_, distance);
}

int ChainCounter_GetValue(const ChainCounter* const self) {
	return BaseCounter_GetValue(&self->base_);
}

long ChainCounter_Remaining(const ChainCounter* const self) {
	return BaseCounter_Remaining(&self->base_);
}
