#include "run_app.h"

#include <stdio.h> /* fprintf() */
#include <stdlib.h> /* atoi() */
					/* exit() */
					/* EXIT_FAILURE (macro) */
					/* EXIT_SUCCESS (macro) */

static void show_usage_and_fail(const char* av0) {
	fprintf(stderr,
			"USAGE: %s %s\n",
					av0, "[days [hours [minutes [seconds]]]]");
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	const char* const prog = argv[0] ? argv[0] : "(null)";
	if (argc > 5) show_usage_and_fail(prog);
	run_app((argc > 1) ? atoi(argv[1]) : 4,
		(argc > 2) ? atoi(argv[2]) : 3,
		(argc > 3) ? atoi(argv[3]) : 2,
		(argc > 4) ? atoi(argv[4]) : 1);
	return EXIT_SUCCESS;
}
