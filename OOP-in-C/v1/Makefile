# Makefile for creating unit tests and demo app for this version
# --------------------------------------------------------------
# below the default for just running `make` can be set :
#
default: run-all-tests

# below the compiler and its options can be set:
Compile=gcc -std=c99

# usually nothing needs to be changed below this line
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TestRunner= assert_based
run-all-tests: $(TestRunner)
	@./$(TestRunner)
$(TestRunner): unit_Test.c ChainCounter.c ChainCounter.h
	$(Compile) -o $@ unit_Test.c ChainCounter.c

run-demo-app: app_main
	@./app_main
app_main: ChainCounter.c ChainCounter.h
app_main: DDD_HH_MM_SS.c
	$(Compile) -o $@ ChainCounter.c DDD_HH_MM_SS.c

clean:
	rm -f $(TestRunner) app_main
realclean: clean
	rm -f a.out core *.o

.PHONY: default
.PHONY: run-all-tests
.PHONY: run-demo-app
.PHONY: clean realclean
