#include "GString.h"

static GStringClass _class;
GStringClass *GStringClass_init(char *name, GStringClass *class) {
    if (class->super) return &_class;
    class->super = GObjClass_init(name, (GObjClass *)class);
    class->_instanceSize = sizeof(GString);
    // class methods...
    return &_class;
}

GString *GString_new_full(Goop *_this, char *name, int value1, int value2) {
    G_CAST(GString, this, _this);
    GStringClass *class = GStringClass_init("GString", &_class);
    if (!this) this = class->alloc(class);
    GObj_new_full((GObj *)this, name);
    this->class = class;
    // instance members...
    return this;
}

GString *GString_new(void) {
    return GString_new_full(NULL, "GString", 8, 8);
}