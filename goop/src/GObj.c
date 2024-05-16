#include <stdarg.h>

#include "GConstants.h"
#include "GObj.h"
#include <time.h>

/* *** local / private functions *** */
// none

/* *** OVERRIDES  *** */
// none

/* *** CLASS METHODS *** */
static void debug(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GObj *this = _THAT_;
    char *msg = $(this)->vformat(fmt, args);
    G_PRINTF("%s(%s): %s\n", this->class->name, this->name, msg);
    va_end(args);
}

static void *warn(char *fmt, ...) {
    // a kinder-gentler 'throw'
    va_list args;
    va_start(args, fmt);
    GObj *this = _THAT_;
    char *msg = $(this)->vformat(fmt, args);
    if (!(this->class->flags & GObjClass_FLAG_QUIET_ON_THROW)) {
        G_PRINTF("WARN: %s('%s'): %s\n", this->class->name, this->name, msg);
    }
    va_end(args);
    return Goop_ERROR;
}

static void *throw(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GObj *this = _THAT_;
    char *msg = $(this)->vformat(fmt, args);
    if (!(this->class->flags & GObjClass_FLAG_QUIET_ON_THROW)) {
        G_PRINTF("ERROR THROWN: %s('%s'): %s\n", this->class->name, this->name, msg);
    }
    if (this->class->flags & GObjClass_FLAG_DIE_ON_THROW) {
        $(this)->die("Exiting due to GObj_FLAG_DIE_ON_THROW = TRUE");
    }
    va_end(args);
    return Goop_ERROR;
}

static void destroy() {
    // we never free memory. we put objects on a "freeList"
    // and reuse them later
    GObj *this = _THAT_;
    G_DEBUG("GObj.destroy: %p:%s\n", this, this->name);
    if (this->flags & GObj_FLAG_DESTROYED) return (void)$(this)->throw("object already destroyed");
    this->flags |= GObj_FLAG_DESTROYED;
    GObj *next = this->class->_freelist;
    this->class->_freelist = this;
    this->userdata = next;
}

static void *alloc(Goop *_class) {
    // we reuse old objects where we can
    // if an object doesn't exist on our freelist, we calloc it
    GObjClass *class = _class;
    GObj *result = class->_freelist;
    G_DEBUG("GObj.alloc: %p:%s\n", result, class->name);
    if (!result) {
        result = calloc(1, class->_instanceSize);
    } else {
        class->_freelist = result->userdata;
        memset(result, 0, class->_instanceSize);
    }
    result->class = class;
    return result;
}

static void die(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GObj *this = _THAT_;
    char *msg = $(this)->vformat(fmt, args);
    G_PRINTF("DIE: %s(%s): %s\n", this->class->name, this->name, msg);
    exit(1);
    va_end(args);
}

static void *clone() {
    GObj *this = _THAT_;
    GObj *dupe = this->class->alloc(this->class);
    G_DEBUG("GObj.clone: %p:%s(%s) -> %p:%s(%s)\n", 
        this, this->class->name, this->name, 
        dupe, dupe->class->name, dupe->name);

    $(this)->update(dupe);
    return dupe;
}

static void *update(void *_obj) {
    // copy this over obj
    // (obj and this should be of the same Class)
    GObj *this = _THAT_;
    G_CAST(GObj, obj, _obj);
    G_DEBUG("GObj.update: %p:%s(%s) -> %p:%s(%s)\n",
        this, this->class->name, this->name,
        obj, obj->class->name, obj->name);
    memcpy(obj, this, this->class->_instanceSize);
    return obj;
}

static char buffer[100];
static char *format(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return buffer;
}

static char *vformat(char *fmt, va_list args) {
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    return buffer;
}

static uint64_t usNow(void) {
    // GUtil *this = _THAT_;
#ifdef PICO_BUILD
        absolute_time_t now = get_absolute_time();
        uint64_t us = to_us_since_boot(now);
        return us;
#else
    struct timespec ts;
    // Use CLOCK_MONOTONIC for a monotonic clock or CLOCK_REALTIME for wall-clock time
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ull + (uint64_t)ts.tv_nsec / 1000;
#endif
}

static uint64_t msNow(void) {
    return usNow() / 1000;
}

/* *** CLASS INITIALIZATION *** */
static GObjClass _class;
static GObjStatics _statics;
GObjClass *GObjClass_init(char *name, GObjClass *class) {
    if (class->_instanceSize > 0) return &_class;
    GObjStatics *statics = &_statics;
    class->super = NULL;
    class->statics = statics;
    class->name = name;
    class->_instanceSize = sizeof(GObj);
    class->_freelist = NULL;
    class->alloc = alloc;
    class->debug = debug;
    class->destroy = destroy;

    statics->throw = throw;
    statics->warn = warn;
    statics->die = die;
    statics->update = update;
    statics->clone = clone;
    statics->format = format;
    statics->vformat = vformat;
    statics->msNow = msNow;
    statics->usNow = usNow;
    return &_class;
}

/* *** CONSTRUCTORS *** */
GObj *GObj_new_full(Goop *_this, char *name) {
    G_CAST(GObj, this, _this);
    G_DEBUG(">> GObj_new_full: %s\n", name);
    GObjClass *class = GObjClass_init("GObj", &_class);
    if (!this) this = class->alloc(class);
    this->class = &_class;
    this->name = name;
    G_DEBUG("<< GObj_new_full: %s\n", this->name);
    return this;
}

GObj *GObj_new(void) {
    return GObj_new_full(NULL, "GObj");
}