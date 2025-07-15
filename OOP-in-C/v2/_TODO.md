## Activities with Version 2

Review the code and its separation to several files.

**Especially make sure to understand the general file structure
required by WOGTEST as you may need to add more tests time.**

### Run the Unit Tests

```sh
make
```

The expected outout again should be that all tests passed.

### Run the Demo Application

```sh
make run-demo-app
```

Figure out how

* exactly the demo application is controlled by command line
  arguments, including what's it behavior is
  * for less than four arguments
  * for more that four arguments
  * for negative argument values
  * for arguments containing not only digits

**Note:** Get into the habit to read the full documentation of
library functions you use, like `atoi`:

https://en.cppreference.com/w/cpp/string/byte/atoi.html

If you have never worked with command line arguments the following
may be relevant too;

https://en.cppreference.com/w/c/language/main_function.html

**Suggestion:** Read the documentation *first* and *predict* what
the demo application will do. Only then run it and verify your
prediction. If your prediction is not met, go back to the
documentation. (*Cppreference.com* is basically a Wiki, so if
some description is easily misunderstood, the user community
itself can fix it.)

## Following Plan A – Get active with some hands-on coding

Replace the `return 0` in `main` with `return EXIT_SUCCESS` for
wider portability. If you think it is a good idea to put comment
after each header file include, which symbol from the header is
used, feel free to do so too.

Also there is an apparent contradiction between the actual
arguments of `run_app` (see `DDD_HH_MM_SS.c`) and the `extern`
declaration suggested in the last step.

Would you consider this to be *Clean Code* or prefer to fix it?

How?

## Following Plan B - Understand what should have been done

If you are also a little bit interested in C++ or have prior
experience with C++ you may now want to do a side-by-side
comparison with *eXtra Version 1* of this series of steps
sub-directory `x1`. You may continue there up to `x4` or skip
the C++ intermezzo and continue to following the main line of
examples with *Version 3* (in sub-directory `v3`).
