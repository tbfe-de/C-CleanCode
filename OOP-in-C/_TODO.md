# Practical Examples

This series of examples demonstrate a number Clean Coding Aspects
as are applicable to the programming language (with a short
excursion to C++. The latter mainly serve to underline the
difficulties to adapt a number of clean coding techniques
introduced by more modern "Object Oriented Programming" (OOP)
Style to C and may well be skipped if you are not interested in
this comparison.

Except for this the series is meant to be worked in order from the
first to the last. Oftentimes "challenges" suggested in the prior
version have their "solution" in the subsequent one.

## Compile and Run

Compilation is from a terminal window controlled by a `Makefile`

**NOTE:** You need not understand the details of that file just to
compile and run.

* `make` -- compiles **and runs** unit tests for the current step.
* `make run-demo-app` compiles (and runs) a small demo application
  for the current step.

**NOTE:**
There are variations to the above explained in a small in a
graphic documenting the initial file structure.


## More Detailed TODO-s

The detailed TODD-files in the individual sub-directory suggest a
common series of activities:

* start with a review to understand the current file structure and
  from on the second step how it extends the previous one;
* identify possible shortcomings which may be
  * "unclean" code intentionally left there to be improved;
  * "complicated" code you do not (yet) fully understand.

Be sure to take notes about these issues so that you can
propose improvements and/or ask informed questions in a later
discussion.

Detailed TODO-s may end with a series of suggested improvements.
Depending on the time you want to spend with the particular step
you have several choices.

* Try yourself some "hands-on" work on the code.
  * It is recommended to first copy all files of that step to a
    new directory.
  * Eg. if you are `v8` create a directory `my_v8,` copy all files
    from `v8` over to it, then make that newly created directory
    your current directory.
  * In a terminal window this means to issue the commands below
    (assuming your current working directory is v8):

```sh
mkdir ../my_v8
cp * ../my_v8
cd ../my_v8
```

== More TBD ==
More detailed description needs to be added. This is also true for
the detailed TODO-s which currently only describe the changes made
so far.
