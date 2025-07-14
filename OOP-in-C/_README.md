# Practical Examples

This series of examples demonstrate a number Clean Coding Aspects
as are applicable to the programming language (with a short
excursion to C++. There is a side path deviating to C++. Following
this os optional and left to those who have some C++ knowledge and
especially understand the difficulty to map typical OOP features
like *Inheritance* and *Late Binding* to C.

Except for this the series is meant to be worked in order from the
first to the last. Oftentimes "challenges" suggested in the prior
version have their "solution" in the subsequent one.

Compilation is from a terminal window controlled by a `Makefile`

**NOTE:** You need not understand the details of that file just to
compile and run.

* `make` -- compiles **and runs** unit tests for the current step.
* `make run-demo-app` compiles (and runs) a small demo application
  for the current step.

## More Detailed TODO-s

The detailed `_TODO.md`-files in the individual sub-directory
suggest a common series of activities:

* start with a review to understand the current file structure and
  for each step how it extends the previous one;
* identify possible shortcomings which may be
  * "unclean" code intentionally left there to be improved;
  * "complicated" code you do not (yet) fully understand.

Consider to take notes about these issues so that you can propose
improvements and/or ask informed questions in a later discussion.

Detailed TODO-s may end with a series of suggested improvements.
Depending on the time you want to spend with the particular step
you have two choices.

* Try yourself some "hands-on" work on the code.
  * there are already prepared sub-directories for going from one
    version to the next;
  * as an example take `v3_to_v4`, which contains all the files
    from version 3, except that the `Makefile` is taken from
    version 4;
  * begin with making the tests compile (plain `make`);
  * only when all tests pass continue with compiling and running
    the demo application (`make run-demo-app`);

* Alternatively or when there is insufficient time fall back to do
  a side-by-side comparison so you can ask better questions when
  a particular step is discussed.