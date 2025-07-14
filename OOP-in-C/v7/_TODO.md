## Activities with Version 7

**Note:** In this version some duplication has been deliberately
left "to be found". If you followed "Plan A" to approach this
step you may already have a better solution yourself.

### Run the Unit Tests

Same as in the previous version – no change in observable
behavior.

### Run the Demo Application

Same as in the previous version – no change in observable
behavior.


## Following Plan A – Get active with some hands-on coding

In accordance with the *DRY*-Principle make sure there is
actually **only one definition** of `struct DDD_HH_MM_SS_` – the
one in file `DDD_HH_MM_SS.h`. This file needs to be included
whenever this structure is referred to.

In accordance with the principle *data hiding* make sure all
access to members of this `struct` is via function calls.

In `main` add a message shown on `stderr` when the program is
called with more than four arguments. In the message the name of
the program and a hint how it would be correctly used should be
included.

In accordance with *SLA* (single level of abstraction) the message
should be issued not from `main? but a separate function called
from `main`. This function then should also terminate the `main`
program and indicate via its return value there was a problem.

In accordance to *design and programm by contract* consult the
reference documentation to decide whether it's necessary to add a
`fflush(stderr)` so that it is guaranteed the message is shown.

In accordance with *POLS* (principle of least surprise) chose the
name of that function to indicate both, that it not only prints
a usage message **but also** terminates the program.

In accordance with *KISS* (keep it simple, stupid) and also the
*Need to Know* decide what the proper visibility of that function
should be.

As good code should not only be "clean" but also "robust" consider
that there is no guarantee the first element of the `argv`-array
in `main` holds the program name - it might also be `NULL`.

## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
