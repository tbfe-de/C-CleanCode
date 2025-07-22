# Makefile for creating unit tests and demo app for this version
# --------------------------------------------------------------
# below the default for just running `make` can be set:
#
default: run-all-tests

# below the compiler and its options can be changed:
Compile=gcc -std=c99

# usually nothing needs to be changed below this line
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TestRunner= gtest_based
run-all-tests: $(TestRunner)
	@./$(TestRunner)
$(TestRunner): my_utils.h my_utils.c
$(TestRunner): SBuffer.h SBuffer.c
$(TestRunner): DDD_HH_MM_SS.h DDD_HH_MM_SS.c
$(TestRunner): DDD_HH_MM_SS_Test.c
$(TestRunner): run_app.c run_app.h
$(TestRunner): run_app_Test.c
$(TestRunner): sbuf_Test.c
$(TestRunner): unit_Test.c main_Test.c
	$(Compile) -o $@ -I.. my_utils.c my_utils_Test.c\
						DDD_HH_MM_SS.c DDD_HH_MM_SS_Test.c\
						SBuffer.c sbuf_Test.c\
						run_app.c run_app_Test.c\
						unit_Test.c main_Test.c

run-demo-app: app_main
	@./app_main
app_main: DDD_HH_MM_SS.c DDD_HH_MM_SS.h
app_main: my_utils.c my_utils.h
app_main: run_app.h run_app.c app_main.c
	$(Compile) -o $@ my_utils.c SBuffer.c\
					DDD_HH_MM_SS.c\
					run_app.c app_main.c

clean:
	rm -f $(TestRunner) app_main
realclean: clean
	rm -f a.out core *.o

.PHONY: run-all-tests
.PHONY: run-demo-app
.PHONY: clean realclean
