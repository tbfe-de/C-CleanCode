#ifndef CHAIN_COUNTER_H
#define CHAIN_COUNTER_H

#include <stddef.h> /* NULL (macro) */

typedef struct ChainCounter_ {
	int range_;
	int value_;
	struct ChainCounter_* next_;
} ChainCounter;

void ChainCounter_Init(ChainCounter* const self, int range, int value, ChainCounter* const next);
int ChainCounter_Step1(ChainCounter* const self);
void ChainCounter_StepN(ChainCounter* const self, int distance);
int ChainCounter_GetValue(const ChainCounter* const self);
long ChainCounter_Remaining(const ChainCounter* const self);

#endif // include guard
