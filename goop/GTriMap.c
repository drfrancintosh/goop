#include "GTriMap.h"

/* *** local / private functions *** */
// none
// (__functionName) {}

/* *** OVERRIDES  *** */
// none
// (_functionName)

/* *** CLASS METHODS *** */
static void **triGet(char *key) {
    // returns ERROR if 'n' is out of bounds
    // returns NULL if 
    // returns a pointer to an array of key, value, and type
    // returns 
    GTriMap *this = _THAT_;
    int n = _(this)->findKey(key);
    if (n == Goop_IERROR) return Goop_ERROR;
    return _(this)->itriGet(n);
}

static void **itriGet(int n) {
    // returns ERROR if 'n' is out of array bounds
    // returns ptr to void *arr[3]
    // arr[0]=key
    // arr[1]=value
    // arr[2]=type
    GTriMap *this = _THAT_;
    this->oldKey = _(this->keys)->get(n);
    if (this->oldKey == Goop_IERROR) return Goop_IERROR;
    this->oldValue = _(this->values)->get(n);
    this->oldType = _(this->types)->get(n);
    return (void **) &this->oldKey;
}

static void **triPut(char *key, void *value,  void *type) {
    GTriMap *this = _THAT_;
    int n = _(this)->findKey(key);
    if (n == 0) {
        n = _(this)->length();
        this->oldKey = _(this->keys)->get(n);
        this->oldValue = _(this->values)->get(n);
        this->oldType = _(this->types)->get(n);
    };
    _(this->keys)->set(n, key);
    return (void **) &this->oldKey;
}

/* *** CLASS INITIALIZATION *** */
static GTriMapClass _class;
GTriMapClass *GTriMapClass_init(char *name, GTriMapClass *class) {
    if (class->super) return &_class;
    class->super = GMapClass_init(name, (GMapClass *)class);
    class->statics = class->super->statics;
    class->_instanceSize = sizeof(GTriMap);
    // class methods...
    class->triGet = triGet;
    class->itriGet = itriGet;
    class->triPut = triPut;
    // overrides ...
    return &_class;
}

/* *** CONSTRUCTORS *** */
GTriMap *GTriMap_new_full(Goop *_this, char *name, int max, int extent) {
    G_CAST(GTriMap, this, _this);
    GTriMapClass *class = GTriMapClass_init("GTriMap", &_class);
    if (!this) this = class->alloc(class);
    GMap_new_full(this, name, max, extent);
    this->class = class;
    // instance member initialization
    this->types = GList_new_full(NULL, "types", max, extent);
    return this;
}

GTriMap *GTriMap_new(void) {
    return GTriMap_new_full(NULL, "GTriMap", 8, 8);
}