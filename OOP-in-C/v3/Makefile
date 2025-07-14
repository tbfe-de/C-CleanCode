# Makefile for creating unit tests and demo app for this version
# --------------------------------------------------------------
# below the default for just running `make` can be set:
#
default: run-all-tests

# below the compiler and its options can be changed:
Compile=g++ -xc++ -std=c++11

# usually nothing needs to be changed below this line
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

TestRunner= gtest_based
run-all-tests: $(TestRunner)
	@./$(TestRunner)
$(TestRunner): ChainCounter.c ChainCounter.h
$(TestRunner): single_Test.c twostage_Test.c multiple_Test.c
$(TestRunner): main_Test.c
	$(Compile) -o $@ -I.. ChainCounter.c\
		single_Test.c twostage_Test.c multiple_Test.c\
		main_Test.c

run-demo-app: app_main
	@./app_main
app_main: ChainCounter.c ChainCounter.h
app_main: DDD_HH_MM_SS.c
	$(Compile) -o $@ ChainCounter.c DDD_HH_MM_SS.c

clean:
	rm -f $(TestRunner) app_main
realclean: clean
	rm -f a.out core *.o

.PHONY: run-all-tests
.PHONY: run-demo-app
.PHONY: clean realclean
