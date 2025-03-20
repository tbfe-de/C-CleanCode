#include "BaseCounter.h"

static void BaseCounter_underflow(BaseCounter* const self) {
    /*empty*/
}

static long BaseCounter_chained(const BaseCounter* const self) {
    return 0L;
}

void (*BaseCounter_virtual[BaseCounter_virtual_size])(void) = {
	(void (*)(void)) BaseCounter_underflow,
	(void (*)(void)) BaseCounter_chained,
};

void BaseCounter_Init(BaseCounter* const self, int const range, int const value) {
	self->vtable_ = &BaseCounter_virtual[0];
	self->range_ = range;
	self->value_ = value;
}

void BaseCounter_Step1(BaseCounter* const self) {
	if (self->value_ == 0)
		((BaseCounter_virtual_underflow_call)
		 (*self->vtable_[BaseCounter_virtual_underflow]))(self);
	else
		--self->value_;
}

void BaseCounter_StepN(BaseCounter* const self, int distance) {
	for (; distance > 0; --distance)
		BaseCounter_Step1(self);
}

int BaseCounter_GetValue(const BaseCounter* const self) {
	return self->value_;
}

long BaseCounter_Remaining(const BaseCounter* const self) {
    return self->value_
		+ ((BaseCounter_virtual_chained_call)
		   (*self->vtable_[BaseCounter_virtual_chained]))(self)
		    * self->range_;
}
