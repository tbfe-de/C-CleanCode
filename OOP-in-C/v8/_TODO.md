## Activities with Version 8

== More TBD ==
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

Also how "bad input" (non-numeric or numneric but out of range)
is currently not quite satisfactory. Let the trainer guide you
through designing and implementing small reusable function that
can be used as "better `atoi`".

## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
