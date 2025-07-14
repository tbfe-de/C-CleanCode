#ifndef DDD_HH_MM_SS_H
#define DDD_HH_MM_SS_H

#include "ChainCounter.h"

struct DDD_HH_MM_SS_ {
	ChainCounter days_;
	ChainCounter hours_;
	ChainCounter minutes_;
	ChainCounter seconds_;
	char display_[14];
};

extern struct DDD_HH_MM_SS_ DDD_HH_MM_SS;

extern void DDD_HH_MM_SS_set(int, int, int, int);
extern void DDD_HH_MM_SS_update(void);
extern void DDD_HH_MM_SS_step(int);
extern long DDD_HH_MM_SS_remaining(void);
extern const char* DDD_HH_MM_SS_display(void);

#endif // include guard
