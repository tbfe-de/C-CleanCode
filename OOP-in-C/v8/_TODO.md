## Activities with Version 8

Finalized clean up of the file structure with header files to be
included everywhere instead of duplicating code for type
definitions and function prototype declarations.

### Run the Unit Tests

Same as in the previous version – no change in observable
behavior.

### Run the Demo Application

The standard behavior when running the program with

```sh
make run-demo-app
```

should not have change. But you need to test the error whether
issuing the usage message works as intended. For that purpose call
the program directly (after having it compiled once):

```sh
./app_main 12 34 56 78 90
```

If you want tho check the return value of `main` use this directly
after the program was run:

```sh
echo $?
```

On Unix-like systems it should be `0` in for `EXIT_SUCCESS` and
`1` for `EXIT_FAILURE`.

## Following Plan A – Get active with some hands-on coding

Add a second way to set the start values for the count-down:
instead of using command line arguments provide those via an
exported shell variable.

Also how "bad input" (non-numeric or numeric but out of range)
is currently not quite satisfactory.

An easier to use and more powerful `atol` and `atof` replacement
could look like this:

* first argument is the `char`-array holding the C-style string
  with the characters to be converted to a numeric value;
* second argument is the address of a `long` or `double` variable
  to be set to the numeric value;
* third argument is the minimum accepted value;
* fourth argument is the maximum accepted value;
* return value is a combination of several error-bits;

```c
enum string_list_fail_bits {
    string_list_err_ok = 0,
    string_list_err_nn = 1<<0,
    string_list_err_lo = 1<<1,
    string_list_err_hi = 1<<2,
};
```

Internally the new functions `



## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
