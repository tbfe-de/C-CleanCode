## Activities with Version 3

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

1. In accordance with the *DRY-Principle* (Don't repeat yourself)
make sure there is actually **only one definition** of
`struct DDD_HH_MM_SS_` – the one in file `DDD_HH_MM_SS.h`. This
file is to be included whenever this `struct` is referred to.

2. In accordance with the principle *Data Hiding* make sure all
access to members of this `struct` is via function calls. (Though
other than C++ in C this cannot be enforced.)

3. For a good *User-Experience* from `main` a message should be
shown on `stderr` when the program is called with more than four
command line arguments. In this message the name of the program
should be included together with a brief hint how it would be
correctly used.

4. In accordance with *SLA* (single level of abstraction) this
message should be issued not from `main` but a separate function
function called from `main`. After showing this message the same
function should also terminate the `main` program. The value
returned to the shell (user ommand line) should and indicate
that there was problem.

5. In accordance to *Design and programming by contract* consult
the reference documentation to decide whether it's necessary to
add an `fflush(stderr)`, to guarantee the message is shown.

6. In accordance with *POLS* (principle of least surprise) chose
the name of that function to indicate both, that it not only prints
a usage message **but also** terminates the program.

7. In accordance with *KISS* (keep it simple, stupid) and also the
*Need to Know* decide what the proper visibility of that function
should be.

As good code should not only be "clean" but also "robust" consider
that there is no guarantee the first element of the `argv`-array
in `main` holds the program name - it might also be `NULL`.

## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
