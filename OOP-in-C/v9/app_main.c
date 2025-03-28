#include "run_app.h"
#include "my_utils.h"

#include <stdbool.h>	/* bool (macro) */
#include <stdio.h>		/* fprintf() */
#include <stdlib.h>		/* atoi() */
						/* exit() */
						/* EXIT_FAILURE (macro) */
						/* EXIT_SUCCESS (macro) */

static const char* PROG;
static void show_usage_and_fail() {
	fprintf(stderr,
			"USAGE: %s %s\n",
					PROG, "[days [hours [minutes [seconds]]]]");
	exit(EXIT_FAILURE);
}

static struct DHMS_ {
	long days_;
	long hours_;
	long minutes_;
	long seconds_;
} DHMS = { 0, 0, 0, 0 };

static int ARGC;
static char** ARGV;
static bool parse_cmdline_args() {
	return (ARGC <= 5)
		&& ((ARGC <= 1) || range_checked_atol(ARGV[1], &DHMS.days_, 0, 999))
		&& ((ARGC <= 2) || range_checked_atol(ARGV[2], &DHMS.hours_, 0, 23))
		&& ((ARGC <= 3) || range_checked_atol(ARGV[3], &DHMS.minutes_, 0, 59))
		&& ((ARGC <= 4) || range_checked_atol(ARGV[4], &DHMS.seconds_, 0, 59))
		;
}

static const char* getenv_or_default(const char* var_name,
									 const char* default_value) {
	const char* env_var = getenv(var_name);
	return env_var ? env_var : default_value;
}

static void preload_from_env_var(const char* name) {
	const char* preload = getenv_or_default(name, "0 1");
	struct string_list_atol_ctl ctl[] = {
		{&DHMS.days_, 0, 999},
		{&DHMS.hours_, 0, 23},
		{&DHMS.minutes_, 0, 59},
		{&DHMS.seconds_, 0, 59},
		{NULL}
	};
	(void)string_list_atol(preload, ctl);
}

int main(int argc, char* argv[]) {
	PROG = argv[0] ? argv[0] : "(null)";
	ARGC = argc;
	ARGV = argv;
	preload_from_env_var("DDD_HH_MM_SS_PRELOAD");
	if (!parse_cmdline_args())
		show_usage_and_fail();
	run_app(DHMS.days_, DHMS.hours_, DHMS.minutes_, DHMS.seconds_);
	return EXIT_SUCCESS;
}
