#include "../gtest/gtest.h"

// these prior tests are disabled as the focus
// know is on the down-counting clock app; the
// test for the counter may be enabled again by
// (1) removing the comments below AND
// (2) adding their `*_Test.c` files accordingly
//      to the build command in the Makefile
//
//TESTCASE(single)
//TESTCASE(twostage)
//TESTCASE(multiple)

// if required add more test groups below
//
TESTCASE(utils_checked)
TESTCASE(utils_slist)
TESTCASE(sbuf)
TESTCASE(demo_app)
TESTCASE(run_app)
// ...
