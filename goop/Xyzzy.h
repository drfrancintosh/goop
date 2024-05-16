#ifndef __Xyzzy__
#define __Xyzzy__

#include "SUPAH.h"

// forward references 
G_FORWARD(Xyzzy)

// constants
enum {
    CONST_NONE = 0x00,
    CONST_ONE = 1,
    CONST_TWO,
}

// members & methods
#define Xyzzy_MEMBERS \
    SUPAH_MEMBERS \
    int member1; \
    int member2; \

#define Xyzzy_METHODS \
    SUPAH_METHODS \
    G_METHOD(int, method1)(int value); \
    G_METHOD(int, method2)(int value); \

// class structs
typedef struct XyzzyClass {
    SUPAHClass *super;
    GObjStatics *statics;
    Xyzzy_METHODS
} XyzzyClass;

typedef struct Xyzzy {
    XyzzyClass *class;
    Xyzzy_MEMBERS
} Xyzzy;

// constructors
extern Xyzzy *Xyzzy_new(void);
extern Xyzzy *Xyzzy_new_full(Goop *this, char *name, int max, int extent);

// class init
extern XyzzyClass *XyzzyClass_init(char *name, XyzzyClass *class);

// satisfy forward references

#endif // __Xyzzy__