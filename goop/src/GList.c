#include "GList.h"

/* *** local / private functions *** */
// none

/* *** OVERRIDES  *** */
static void _debug(char *msg, ...) {
    GList *this = _THAT_;
    G_PRINTF("%s(%s): %s\n", this->class->name, this->name, msg);
    G_PRINTF("...length: %d\n", this->length);
    G_PRINTF("...max: %d\n", this->max);
    G_PRINTF("...extent: %d\n", this->extent);
    G_PRINTF("...list: %p\n", this->list);
    for (int i = 0; i < this->length; i++)
        G_PRINTF("...list[%d]: %s\n", i, this->list[i]);
}

/* *** CLASS METHODS *** */
static void *insert(int n, void *ptr) {
    GList *this = _THAT_;
    G_DEBUG(">> GList.insert(%d, %s)\n", n, ptr);
    if (n > this->length) {
        return $(this)->throw("ERROR: insert(n=%d): n is larger than length=%d", n, this->length);
    }
    this->length++;
    if (this->length > this->max) {
        if (this->extent == 0)
            return $(this)->throw("ERROR: insert(n=%d): cannot extend: length=%d extent=%d", n, this->length, this->extent);
        this->max += this->extent;
        this->list = G_REALLOC(this->list, this->max, void *);
    }
    G_MEMMOVE(&this->list[n + 1], &this->list[n], (this->length - n - 1), void *);
    this->list[n] = ptr;
    G_TRACE("<< GList.insert(%d, %s)\n", n, ptr);
    return ptr;
}

// this method must be named _remove not to conflict with the remove() method in stdio.h
static void *_remove(int n) {
    GList *this = _THAT_;
    if (n < 0 || n >= this->length)
        return $(this)->throw("'ERROR: remove(n=%d) out of range: length=%d", n, this->length);
    void *result = this->list[n];
    int toRemove = this->length - n - 1;
    if (toRemove) G_MEMMOVE(&this->list[n], &this->list[n + 1], toRemove, void *);
    this->length--;
    return result; // return removed pointer
}

static void *push(void *ptr) {
    GList *this = _THAT_;
    G_TRACE(">> GList.push(%s)\n", ptr);
    void *result = _(this)->insert(this->length, ptr);
    G_TRACE("<< GList.push(%s)\n", ptr);
    return result;
}

static void *pop(void) {
    GList *this = _THAT_;
    void *result = _(this)->remove(this->length - 1);
    return result;
}

static void *set(int n, void *ptr) {
    GList *this = _THAT_;
    if (n < 0 || n >= this->length)
        return $(this)->throw("'ERROR: set(n=%d) out of range: length=%d", n, this->length);
    this->list[n] = ptr;
    return ptr;
}

static void *get(int n) {
    GList *this = _THAT_;
    if (n < 0 || n >= this->length)
        return $(this)->throw("'ERROR: get(n=%d) out of range: length=%d", n, this->length);
    return this->list[n];
}

static int isEmpty() {
    GList *this = _THAT_;
    return this->length == 0;
}

static int length() {
    GList *this = _THAT_;
    return this->length;
}

/* *** CLASS INITIALIZATION *** */
static GListClass _class;
GListClass *GListClass_init(char *name, GListClass *class) {
    if (class->super) return &_class;
    class->super = GObjClass_init(name, (GObjClass *)class);
    class->_instanceSize = sizeof(GList);
    // class methods...
    class->push = push;
    class->pop = pop;
    class->insert = insert;
    class->remove = _remove;
    class->get = get;
    class->set = set;
    class->isEmpty = isEmpty;
    class->length = length;
    // overrides...
    class->debug = _debug; 
    return &_class;
}

/* *** CONSTRUCTORS *** */
GList *GList_new_full(Goop *_this, char *name, int max, int extent) {
    G_CAST(GList, this, _this);
    GListClass *class = GListClass_init("GList", &_class);
    if (!this) this = class->alloc(class);
    GObj_new_full(this, name);
    this->class = class;
    this->length = 0;
    this->max = max;
    this->extent = extent;
    this->list = G_CALLOC(this->max, void *);
    return this;
}

GList *GList_new(void) {
    return GList_new_full(NULL, "GList", 8, 8);
}