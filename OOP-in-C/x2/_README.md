## Explanations for eXtra Version 2

Another C++ version in which the class design now us based on
inheritance and virtual member functions. Both are core features
of C++ with no equivalent in C.

**Note:** Missing such features in C you can

* neither build on the *Liskov Substitution Principle*
* nor on *Late Binding* (aka. *Dynamic Binding*)
* as implemented by `virtual` member functions in C++.

As a consequence many *Design Patterns* used in OOP-Languages
(eg. the *Template Method*) and *Best Practices* (like *NVI* =
*Non-Virtual-Interface*) cannot be used. In effect this eliminates
about half of the *Solid Principles*, which often are closely
associated with *Clean Code*.
