#ifndef DDD_HH_MM_SS_H
#define DDD_HH_MM_SS_H

#include "ChainCounter.h"

#include "SBuffer.h"

typedef struct DDD_HH_MM_SS_ {
	ChainCounter days_;
	ChainCounter hours_;
	ChainCounter minutes_;
	ChainCounter seconds_;
	SBuffer* display_;
} DDD_HH_MM_SS;

void DDD_HH_MM_SS_Init(DDD_HH_MM_SS*, SBuffer*);
void DDD_HH_MM_SS_set(DDD_HH_MM_SS*, int, int, int, int);
void DDD_HH_MM_SS_step(DDD_HH_MM_SS*, int);
long DDD_HH_MM_SS_remaining(const DDD_HH_MM_SS*);
void DDD_HH_MM_SS_display(const DDD_HH_MM_SS*);
void DDD_HH_MM_SS_run(DDD_HH_MM_SS*);

#endif // include guard
