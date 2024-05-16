#ifndef __GObj__
#define __GObj__

#include "Goop.h"
#include "GConstants.h"

// forward references 
G_FORWARD(GObj);

// constants

// members & methods
#define GObj_MEMBERS \
    char *name; \
    void *userdata; \
    int flags; \

#define GObj_METHODS \
    char *name; \
    int flags; \
    int _instanceSize; \
    GObj *_freelist; \
    G_METHOD(void, debug)(char *fmt, ...); \
    G_METHOD(void, destroy)(void); \
    G_METHOD(void *, alloc)(void *clazz); \

/**
 * STATICS are generally not inherited or overridden
 * The also are expected to not modify the instance variables
 * of the calling object. However, if an object is passed as an argument
 * then it may be modified as a side effect.
 * 
 * STATICS are invoked with the DOLLAR-SIGN `$(this)->xxx()` macro.
 * This is also a questionable mechanism as now the user must 
 * memorize which methods are "overridable" and which are "static".
 * 
 * STATICS may also be thought of as SERVICES. As such, they resemble
 * cross-cutting utilities. This is open to abuse. For example the msNow()
 * and usNow() methods are STATICS that likely should be part of another library.
 * 
 * STATICS were created as a way of reducing the number of METHODS
 * that were inherited by child classes.
 * 
 * While it's expected that STATICS are not inherited or overridden, there are two
 * exceptions to this rule:
 * 1. One can use the same macro expansion mechanism to extend STATICS as CLASSES
 * 2. One can also emply "monkey patchs" where you override one of the STATIC methods
 *    and it has an immediate effect on all objects in the system. This may be 
 *    considered either a bug or a feature.
*/
#define GObj_STATICS \
    G_METHOD(void *, throw)(char *fmt, ...); \
    G_METHOD(void *, warn)(char *fmt, ...); \
    G_METHOD(void, die)(char *fmt, ...); \
    G_METHOD(void *, clone)(void); \
    G_METHOD(void *, update)(void *obj); \
    G_METHOD(char *, format)(char *fmt, ...); \
    G_METHOD(char *, vformat)(char *fmt, va_list args); \
    G_METHOD(uint64_t, msNow)(void); \
    G_METHOD(uint64_t, usNow)(void); \

// class structs
typedef struct GObjStatics {
    GObj_STATICS
} GObjStatics;

typedef struct GObjClass {
    void *super;
    GObjStatics *statics;
    GObj_METHODS
} GObjClass;

typedef struct GObj {
    GObjClass *class;
    GObj_MEMBERS
} GObj;

// constructors
extern GObj *GObj_new(void);
extern GObj *GObj_new_full(Goop *this, char *name);

// class init
extern GObjClass *GObjClass_init(char *name, GObjClass *class);

#endif // __GObj__