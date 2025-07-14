#ifndef BASE_COUNTER_H
#define BASE_COUNTER_H

typedef struct BaseCounter_ {
	void (**vtable_)(void);
	int range_;
	int value_;
} BaseCounter;

typedef void (*BaseCounter_virtual_underflow_call)(BaseCounter*);
typedef long (*BaseCounter_virtual_chained_call)(const BaseCounter*);

enum { BaseCounter_virtual_underflow = 0,
       BaseCounter_virtual_chained = 1,
	   BaseCounter_virtual_size = 2
};

extern void (*BaseCounter_virtual[BaseCounter_virtual_size])(void);

void BaseCounter_Init(BaseCounter* const self, int const range, int const value);
void BaseCounter_Step1(BaseCounter* const self);
void BaseCounter_StepN(BaseCounter* const self, int const distance);
int BaseCounter_GetValue(const BaseCounter* const self);
long BaseCounter_Remaining(const BaseCounter* const self);

#endif // include guard
