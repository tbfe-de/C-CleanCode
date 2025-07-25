# Activities with Version 1

## Run the Unit Tests

```sh
make
```

The result should look something like this:

```txt
gcc -std=c99 -o assert_based unit_Test.c ChainCounter.c
** unit tests passed **
```

If you repeat the `make` command the first line (showing the
command to compile the program) will not appear again. Unless of
course you first do this:

```sh
make clean
```

This removes all the intermediate files created intentionally or
unintentionally.

**NOTE:** The use of a `Makefile` to control the compilation (and
in this case also running the compiled executable) is a deliberate
choice. In real projects meanwhile *CMake* is used, for good
reasons. But in more basic training with only a handful of source
files, like this one, *CMake* is a less transparent wrt.
dependencies. In comparison, building the executable(s) based on
the explicit description in a `Makefile` much better shows what's
really going on behind the scenes.

**If a majority of participants wants to learn the basics of a
`Makefile`-based build, we can spend a few minutes on this topic,
though it's only loosely related to "Clean Code in C".**

## Run the Demo Application

```sh
make run-demo-app
```

The full result should end with something like this:

```txt
gcc -std=c99 -o app_main ChainCounter.c DDD_HH_MM_SS.c
  4d03h02m01s -- next: 6808 steps of 356521 remaining
  4d01h08m33s -- next: 5250 steps of 349713 remaining
  3d23h41m03s -- next:   74 steps of 344463 remaining
...
  0d10h01m39s -- next: 7802 steps of 36099 remaining
  0d07h51m37s -- next: 6854 steps of 28297 remaining
  0d05h57m23s -- next:  978 steps of 21443 remaining
  0d05h41m05s -- next: 7409 steps of 20465 remaining
  0d03h37m36s -- next: 8229 steps of 13056 remaining
  0d01h20m27s -- next: 4827 steps of 4827 remaining
  0d00h00m00s -- DONE
```

This shows a "Countdown Clock" output (obviously) measuring in
*days*, *hours*, *minutes*, and *seconds*. The start time is 4
days, 3 hours, 2 minutes, and 1 second. (For brevity part of the
output has been deleted from the middle.)

You can run the demo application again with different start values
this way:

```sh
./app_demo 0 5 30 10
```

This runs the countdown starting from 5 hours, 30 minutes, and 15
seconds:

```txt
  0d05h30m15s -- next: 6808 steps of 19815 remaining
  0d03h36m47s -- next: 5250 steps of 13007 remaining
  0d02h09m17s -- next:   74 steps of 7757 remaining
  0d02h08m03s -- next: 3659 steps of 7683 remaining
  0d01h07m04s -- next: 4024 steps of 4024 remaining
  0d00h00m00s -- DONE
```

## Following Plan A – Get active with some hands-on coding

REMINDER: you should do this kind of work in the sub-directory
`v1_to_v2` which has been prepared with all the files from the
sub-directory `v1` plus the `Makefile` from `v2.

1. Understand that there are actually two `main` programs:
   * one is is part `DDD_HH_MM_SS.c`,
   * the other is part of `unit_Test.c`
   * for a better *Separation of Responsibilities* (SRP)
     * **create a new file `app_main.cpp`** and  
     * **move the `main` program from `DDD_HH_MM_SS.c` into it**

With `main` now moved to its own translation unit you need at
least this in `app_main.cpp` too:

```c
extern int run_app();
```

Why is this?

------------------------------------------------------------------

Use `make run-demo-app` to verify everything that once worked
still works and gives the expected result. If anything needs to be
fixed, do it before you continue.

------------------------------------------------------------------

2. Complete some of the currently commented-out tests. After each
   single one you complete run all the tests again.

   Completing ALL the commented-out tests is a lot o work and
   probably not worth it. If you already have experience with a
   more advanced framework for unit tests you'll probably already
   see the drawbacks of assert`-ion based testing. What are they?

------------------------------------------------------------------

3. Understand that falling back to `assert`-ion based is just a
   minimum and done in this first version just to get you into
   the *TDD Mindset*. But in practice the approach is clumsy and
   from on the version 2 *WOGTEST* is used as test framework.

   (The C++ related side-step `x1`to `x4` of the main sequence
   `v1` to `v4` continues with `assert`-ion based testing. So
   you can take `x1` as a solution to `v1`.

------------------------------------------------------------------

## Following Plan B - Understand what should have been done

Do a "side by "side" comparison and try to reason why the changes
made improved the cleanliness of the code. In this reasoning
include the files newly were created to which then code of already
existing files has been moved. (Is this still KISS? Is it YAGNI?)
