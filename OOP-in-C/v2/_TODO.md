## Activities with Version 2

Review th code and its separation to several files.

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

**Note:** Get accustomed to read the documentation for `atoi`here:

https://en.cppreference.com/w/cpp/string/byte/atoi.html

If you have never worked with command line arguments the following
may be relevant too;

https://en.cppreference.com/w/c/language/main_function.html

**Suggestion:** Read the documentation *first* and *predict* what
the demo application will do. Only then run it and verify your
prediction. If your prediction is not met, go back to the
documentation. (*Cppreference.com* is basically a Wiki, so if
some description is easily misunderstood, the user community
itself can fix it.

## Following Plan A – Get active with some hands-on coding

In this particular case it is probably no option, as the solution
in version 3 is the same program written in C++. So you may either
go with Plan B or completely skip this and go to version 5

## Following Plan B - Understand what should have been done

If you are at least a little bit interested in C++ or have prior
experience with C++ you may now want to do a side-by-side
comparison with Version 3.
