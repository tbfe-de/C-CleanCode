## Activities with Version 6

### Run the Unit Tests

Same as in the previous version – no change in observable
behavior. Also timing should be exactly the same, as the macros
only hide previously explicit code.

### Run the Demo Application

Same as in the previous version – no change in observable
behavior.

## Following Plan A – Get active with some hands-on coding

Turn back to the design with only the `ChainCounter` pointing to
the next counter (if any), as a classic OOP-design will mostly
cause complications, not easier to understand code.

**Note:** Instead of "turning back from object oriented C with
inheritance and late binding" (as in this version from version 6)
it is easier to start with the code of version 2.

Take this as a chance to make other improvements, like more
modular approach following *Single Responsibility Principle* by
putting `run_app` in a file of its own (`run_app.c`) with the
appropriate function prototype in a header file (`run_app.h`).

From a "maximum portability" aspect also returning `0` from the
`main` function to indicate success should be revised.

## Following Plan B - Understand what should have been done

If you want to go with a side-by-side comparison only it rather
makes sense to compare version 7 to version 2 (not this version).

**Note:** Also version 7 is not yet as "clean" as can be, as there
is still some "duplication", contradicting the *DRY* principle.
