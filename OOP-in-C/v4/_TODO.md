## Activities with Version 4

The C++ line still continues for this one version.

**Skip this if only interested in C**

Now the class design uses inheritance and virtual member
functions. Both are core features of C++ that have no real
equivalent in C.

**Note:** Missing such features in C you neither can build on the
*Liskov Substitution Principle* nor *Late Binding* (aka. *Dynamic
Binding*) as implemented by `virtual` member functions in C++.

The direct consequence is that typical *Design Patterns* used in
OOP-Languages (as eg. the *Template Methode*) and *Best Practices*
(like *NVI* = *Non-Virtual-Interface*) cannot be used. In effect
this eliminates applying most of the *Solid Principles*, which
often are closely associated with *Clean Code*.

### Run the Unit Tests

Same as in the previous version – no change in observable
behavior. Except maybe when timing the code for its performance,
as *late binding adds some run-time cost.

### Run the Demo Application

Same as in the previous version – no change in observable
behavior.

## Following Plan A – Get active with some hands-on coding

Again, actually programming C++ is probably not what is expected
in this course. Either continue with version 4 or follow Plan B.

## Following Plan B - Understand what should have been done

Do a side-by-side comparison of the two C++ versions. Which one
appears to be "more clean" from the aspect of coding. If you have
never used a language like C++, Java, C#, incrTcl … which at least
provide inheritance and late binding, the answer is probably just
a gut-feeling.
