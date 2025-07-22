## Activities with Version 5

Review in the `main` program and in the `my_utils` related header
implementation files how these new functions work.

* `range_checked_atol`,
* `range_checked_atof`,
* `string_list_atol`, and
* `string_list_atof`

If you are unsure how they are applied you may also have a look
into the related unit tests.

**Note 1**: The latter are "table-controlled" clean solution to
pass-in white-space separated values extracted from a character
string.

* This may also be called the *Table-Driven Algorithm Idiom* and
* extends to the even more general *Little Languages* approach.

**Note 2**: It's not quite *YAGNI* that there is already
functionality implemented which is not needed in the current
project. But at least there are already tests.

### Run the Unit Tests

As usual.

### Run the Demo Application

Try both, "good" and "bad" input, both as command line arguments
and from the environment variable `DDD_HH_MM_SS_PRELOAD`. How
environment variable are set may vary with the Shell you use.

Typically something this works:

```sh
DDD_HH_MM_SS_PRELOAD='10 20 30 40'
export DDD_HH_MM_SS_PRELOAD
```

If you want to know whether the variable was set use:

```sh
env | grep DDD_HH_MM_SS_PRELOAD
```

## Following Plan A – Get active with some hands-on coding

Make the randomly generated maximum distance of the next
count-down configurable with another command line argument (or a
value handed over via the preset environment variable).

## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
