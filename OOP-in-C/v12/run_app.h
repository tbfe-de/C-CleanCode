#ifndef RUN_APP_H
#define RUN_APP_H

#include "DDD_HH_MM_SS.h"

typedef struct RDHMS_ {
    long rlimit_;
	long days_;
	long hours_;
	long minutes_;
	long seconds_;
} RDHMS;

typedef struct APP_ {
    DDD_HH_MM_SS countdown_;
} APP;

void APP_Init(APP *self);
void APP_run(APP *self, RDHMS params);

#endif // include guard
