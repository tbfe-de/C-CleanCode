#include "../gtest/gtest.h"

#include "c_calls.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

char output[256];

struct StaticClass_ {
    const char text_[20];
} StaticClass = {
    "static class"
};

const char* StaticClass_GetText() {
    return StaticClass.text_;
}

TEST(c_calls, scall) {
    snprintf(output, sizeof output, "comes from: %s",
             SCALL_(StaticClass, GetText));
        // same as: StaticClass_GetText()

    EXPECT_STREQ("comes from: static class", output);
}

typedef struct InstantiableClass_ {
    char text_[20];
} InstantiableClass;

void InstantiableClass_Init(InstantiableClass* self,
                            char const* text) {
    const size_t N = (sizeof self->text_)-1;
    strncpy(self->text_, text, N)[N] = '\0';
}
const char* InstantiableClass_GetText(const InstantiableClass* self) {
    return self->text_;
}

TEST(c_calls, dcall) {
    InstantiableClass obj;
    InstantiableClass_Init(&obj, "instantiable class");
    snprintf(output, sizeof output, "comes from: %s",
             DCALL_(InstantiableClass, obj, GetText));
        // same as: InstantiableClass_GetText(&obj)
    EXPECT_STREQ("comes from: instantiable class", output);
}

typedef struct Base_ {
    void (**vtable_)(void);
    int a_;
    int b_;
} Base;

enum {
    Base_virtual_m1 = 0,    // all virtual methods to be defined
    Base_virtual_m2 = 1,    // later are first enumerated here
                            // ... there can be many more ...
    Base_virtual_SIZE = 2   // total number of such methods
};

typedef void (*Base_virtual_m1_call)(Base*, const char*, size_t); // define call types
typedef const char* (*Base_virtual_m2_call)(Base*);        // ... for all of the above

// define base class implementations of `m1` ...
void Base_m1(Base* self, char out[], size_t sz) {
    strncpy(out, "Base::m1", sz-1)[sz-1] = '\0';
}
// define base class implementations of `m2` ...
const char* Base_m2(Base* self) {
    return "Base::m2";
}
// ... and populate table, paying attention to order!!
void (*Base_virtual[Base_virtual_SIZE])(void) = {
	(void (*)(void)) Base_m1,
	(void (*)(void)) Base_m2,
};

void Base_Init(Base* self) {
    self->a_ = 0;
    self->b_ = 0;
    self->vtable_ = Base_virtual;
};

typedef struct Derived_ {
    Base base_;
    // ...
} Derived;

enum {
    Derived_virtual_m1 = Base_virtual_m1,
    Derived_virtual_m2 = Base_virtual_m2,
    Derived_virtual_SIZE = Base_virtual_SIZE
};

typedef void (*Derived_virtual_m1_call)(Derived*, const char*, size_t);
typedef const char* (*Derived_virtual_m2_call)(Derived*);

// re-define derived class implementations of `m2` ...
const char* Derived_m2(Derived* self) {
    return "Derived::m2";
}
// ... and populate table, keeping not re-defined ones
void (*Derived_virtual[Derived_virtual_SIZE])(void) = {
	(void (*)(void)) Base_m1,
	(void (*)(void)) Derived_m2,
};

void Derived_Init(Derived* self) {
    Base_Init(&self->base_);
    self->base_.vtable_ = Derived_virtual;
}

typedef struct MoreDerived_ {
    Derived base_;
    // ...
} MoreDerived;

enum {
    MoreDerived_virtual_m1 = Derived_virtual_m1,
    MoreDerived_virtual_m2 = Derived_virtual_m2,
    MoreDerived_virtual_m3 = 2,
    MoreDerived_virtual_SIZE = 3
};

typedef void (*MoreDerived_virtual_m1_call)(MoreDerived*, const char*, size_t);
typedef const char* (*MoreDerived_virtual_m2_call)(MoreDerived*);
typedef const char* (*MoreDerived_virtual_m3_call)(MoreDerived*);

// re-define derived class implementations of `m3` ...
const char* MoreDerived_m3(MoreDerived* self) {
    return "MoreDerived::m3";
}
// ... and populate table, adding another entry
void (*MoreDerived_virtual[MoreDerived_virtual_SIZE])(void) = {
	(void (*)(void)) Base_m1,
	(void (*)(void)) Derived_m2,
    (void (*)(void)) MoreDerived_m3
};

void MoreDerived_Init(MoreDerived* self) {
    Derived_Init(&self->base_);
    self->base_.base_.vtable_ = MoreDerived_virtual;
}

TEST(c_calls, base) {
    Base obj;
    Base_Init(&obj);
    VCALL_2(Base, obj, m1, output, sizeof output);
    EXPECT_STREQ("Base::m1", output);
    EXPECT_STREQ("Base::m2", VCALL_(Base, obj, m2));
}

TEST(c_calls, derived) {
    Derived obj;
    Derived_Init(&obj);
    VCALL_2(Derived, obj, m1, output, sizeof output);
    EXPECT_STREQ("Base::m1", output);
    EXPECT_STREQ("Derived::m2", VCALL_(Derived, obj, m2));
}

TEST(c_calls, more_derived) {
    MoreDerived obj;
    MoreDerived_Init(&obj);
    VCALL_2(MoreDerived, obj, m1, output, sizeof output);
    EXPECT_STREQ("Base::m1", output);
    EXPECT_STREQ("Derived::m2", VCALL_(MoreDerived, obj, m2));
    EXPECT_STREQ("MoreDerived::m3", VCALL_(MoreDerived, obj, m3));
}
