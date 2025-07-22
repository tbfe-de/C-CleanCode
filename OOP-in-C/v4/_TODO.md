## Activities with Version 4

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

should not change. To test the error whether issuing the usage
message works as intended call the program directly from the shell
command line (after it has been compiled):

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

Note that this is a big refactoring and in a fictitious story
about the "history" of "Count-Down Demo App", how it might have
evolved and further developed e.g. as suggestions from a code
review. In the fictitious story all the points made below were
discussed in regard of their pro's and con's and the whole team
then decided whether to follow or not.

So, of course, you are essentially free what you do in this step
of the exercise but if you want to compare your solution with the
example solution solution shown in the next step you need to
follow the decision made here.

1. For communication between various parts of the `app_main.c`
   translation unit, the command line arguments received by `main`
   as arguments on the stack should rather be put into global
   variables (proposed names: `ARGC` and `ARGV`).

   Discussing the pro's and con's lead to the decision to
   implement this change as first step of the larger refactoring.

2. The command line arguments should be better checked whether
   they are valid integral number and in the correct limits for
   what they initialize (0..59 for minutes and seconds, 0..23 for
   hours and 0..999 for days).

   Several possible solutions were discussed but though some were
   off the table soon, like:
   * using standard library function `atoi` and scan the argument
     before for non-digit characters
   * using the standard library function `strol` surrounded by
     boiler plate code to find up to which part the character
     string was convertible to a number.

   Finally the KISS and YAGNI side lost and the decision was made
   in favor of DRY, SRP, SLA, and "reusability" tio develop a new
   function `range_checked_atol` that can be called as follows:
   * **1st argument:** the string to be converted (as usual in C
     a pointer to the first character of an array of characters,
     ending with a `\0`-character;
   * **2nd argument:** the address of the `int`-variable
     to receive the converted value;
   * **3rd argument:** acceptable lower bound of the conversion;
   * **4th argument:** acceptable upper bound if the conversion;
   The return value of that function should indicate whether the
   conversion was successful and the result is within the bounds.

   To make quick progress the decision was made to have the
   development made by a split-off sub-team, which immediately
   subdivided again in one team implementing the unit tests and
   the other one the actual function.

   So that the main team could continue working in parallel the
   following mock implementation was agreed on:
   ```
   int range_checked_atol(const char* s, const long *result, long min, long max) {
        *result = atol(s);
        return 0;
   }
   ```
   (Preceding the decision to indicate success by returning `0`
   was a lengthy discussion whether POLS wouldn't demand to use
   a positive number for success and zero for failure, as in C
   this would "naturally" represent `true` and `false`i. But

   worthwhile to indicate but success is unique. And POLS-wise `0`
   can also be taken to mean: *"there have been 0 errors"*).

3. Finally there was a (fictitious) demand from the (fictitious)
   user community of the *Countdown Demo Application* to have a
   way to "store" the command line arguments in advance in a place
   from which they could be easily retrieved by the application
   itself. It was decided that an environment variable exported
   from the command line interpreter) were an adequate KISS
   solution. To implement something "more advanced" use a file
   with JSON syntax (or an early MS-Windows `ini`-file style) or
   maybe a full blown general *User Preferences Settings Facility*
   were clearly YAGNI.

   Yet, a proposal based on a on a variadic function was neither
   considered "clean" nor robust and different ideas were actively
   discussed.

   ```

The trainer will guide you through a "write your tests first"
approach to implement these replacements.

## Following Plan B - Understand what should have been done

Do a side-by-side comparison with the next version.
