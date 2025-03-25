#include "run_app.h"

#include "my_utils.h"

#include <stdbool.h>	/* bool (macro) */

#include <stdio.h>		/* fprintf() */
#include <stdlib.h>		/* atoi() */
						/* exit() */
						/* EXIT_FAILURE (macro) */
						/* EXIT_SUCCESS (macro) */

#define RLIMIT_BAKED_IN_MAXIMUM (10*1000)

static const char* PROG;
static void show_usage_and_fail() {
	fprintf(stderr,
			"USAGE: %s %s\n",
					PROG, "[rlimit [days [hours [minutes [seconds]]]]]");
	exit(EXIT_FAILURE);
}

static const char* getenv_or_default(const char* name, const char* deflt) {
	const char* env_var = getenv(name);
	return env_var ? env_var : deflt;
}

static int ARGC;
static char** ARGV;

static RDHMS params = {	// the values below are the backed-i defaults
	.rlimit_ = RLIMIT_BAKED_IN_MAXIMUM,
	.days_ = 1,
	.hours_ = 0,
	.minutes_ = 0,
	.seconds_ = 0,
};
static bool parse_cmdline_args() {
	return (ARGC <= 6)
		&& ((ARGC <= 1) || range_checked_atol(ARGV[1], &params.rlimit_, 2, RLIMIT_BAKED_IN_MAXIMUM))
		&& ((ARGC <= 2) || range_checked_atol(ARGV[2], &params.days_, 0, 999))
		&& ((ARGC <= 3) || range_checked_atol(ARGV[3], &params.hours_, 0, 23))
		&& ((ARGC <= 4) || range_checked_atol(ARGV[4], &params.minutes_, 0, 59))
		&& ((ARGC <= 5) || range_checked_atol(ARGV[5], &params.seconds_, 0, 59))
		;
}

static void preload_from_env_var(const char* name) {
	const char* preload = getenv_or_default(name, "1 1");
	struct string_list_atol_ctl ctl[] = {
		{&params.rlimit_, 2, RLIMIT_BAKED_IN_MAXIMUM},
		{&params.days_, 0, 999},
		{&params.hours_, 0, 23},
		{&params.minutes_, 0, 59},
		{&params.seconds_, 0, 59},
		{NULL}
	};
}

int main(int argc, char* argv[]) {
	PROG = argv[0] ? argv[0] : "(null)";
	ARGC = argc;
	ARGV = argv;
	preload_from_env_var("DDD_HH_MM_SS_PRELOAD");
	if (!parse_cmdline_args())
		show_usage_and_fail();
// - - - - - - - - - - - - - - - - - - -
	char huge[100*1000];
	SBuffer output = SBuffer_INIT(huge);
	APP the_app;
	APP_Init(&the_app);
	APP_run(&the_app, params, &output);
	puts(output.static_buffer);
// - - - - - - - - - - - - - - - - - - -
	return EXIT_SUCCESS;
}
