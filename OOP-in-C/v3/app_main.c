#include <stdlib.h>	/* atoi() */
					/* EXIT_SUCCESS (macro) */

extern void run_app(int, int, int, int);

int main(int argc, char* argv[]) {
	run_app((argc > 1) ? atoi(argv[1]) : 4,
			(argc > 2) ? atoi(argv[2]) : 3,
			(argc > 3) ? atoi(argv[3]) : 2,
			(argc > 4) ? atoi(argv[4]) : 1);
	return EXIT_SUCCESS;
}
