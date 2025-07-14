## Explanations for eXtra Version 2

The C++ line continues for this one version.

Now the class design uses inheritance and virtual member
functions. Both are core features of C++ with no equivalent in C.

**Note:** Missing such features in C you

* neither can build on the *Liskov Substitution Principle*
* nor on *Late Binding* (aka. *Dynamic Binding*) as implemented by
  `virtual` member functions in C++.

The direct consequence is that many *Design Patterns* used in
OOP-Languages (as eg. the *Template Method*) and *Best Practices*
(like *NVI* = *Non-Virtual-Interface*) cannot be used. In effect
this eliminates half of the *Solid Principles*, which often are
closely associated with *Clean Code*.
