#include "Xyzzy.h"

/* *** local / private functions *** */
// none
// (__functionName) {}

/* *** OVERRIDES  *** */
// none
// (_functionName)

/* *** CLASS METHODS *** */
static int method1(int value) {
    Xyzzy *this = _THAT_;
    return value;
}

static int method2(int value) {
    Xyzzy *this = _THAT_;
    return value;
}


/* *** CLASS INITIALIZATION *** */
static XyzzyClass _class;
XyzzyClass *XyzzyClass_init(char *name, XyzzyClass *class) {
    if (class->super) return &_class;
    class->super = SUPAHClass_init(name, (SUPAHClass *)class);
    class->statics = class->super->statics;
    class->_instanceSize = sizeof(Xyzzy);
    // class methods...
    class->method1 = method1;
    class->method2 = method1;
    // overrides ...
    return &_class;
}

/* *** CONSTRUCTORS *** */
Xyzzy *Xyzzy_new_full(Goop *_this, char *name, int value1, int value2) {
    G_CAST(Xyzzy, this, _this);
    XyzzyClass *class = XyzzyClass_init("Xyzzy", &_class);
    if (!this) this = class->alloc(class);
    SUPAH_new_full(this, name);
    this->class = class;
    // instance member initialization
    this->member1 = value1;
    this->member2 = value2;
    return this;
}

Xyzzy *Xyzzy_new(void) {
    return Xyzzy_new_full(NULL, "Xyzzy", 8, 8);
}