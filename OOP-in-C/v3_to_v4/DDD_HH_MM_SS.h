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

#endif // include guard
