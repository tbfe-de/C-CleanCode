#ifndef CHAIN_COUNTER_H
#define CHAIN_COUNTER_H

#include "BaseCounter.h"

typedef struct ChainCounter_ {
	BaseCounter base_;
	BaseCounter* next_;
} ChainCounter;

extern void (*ChainCounter_virtual[BaseCounter_virtual_size])(void);

void ChainCounter_Init(ChainCounter* const self, const int range,
                       const int value, BaseCounter* const next);
void ChainCounter_Step1(ChainCounter* const self);
void ChainCounter_StepN(ChainCounter* const self, int const distance);
int ChainCounter_GetValue(const ChainCounter* const self);
long ChainCounter_Remaining(const ChainCounter* const self);

#endif // include guard
