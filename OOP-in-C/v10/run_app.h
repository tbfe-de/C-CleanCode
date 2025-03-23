#ifndef RUN_APP_H
#define RUN_APP_H

typedef struct RDHMS_ {
    long rlimit_;
	long days_;
	long hours_;
	long minutes_;
	long seconds_;
} RDHMS;

void run_app(const RDHMS);

#endif // include guard
