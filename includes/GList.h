#ifndef __GList__
#define __GList__

#include "GObj.h"

// forward references 

// constants

// members & methods

#define GList_MEMBERS \
    GObj_MEMBERS \
    void **list; \
    int length; \
    int max; \
    int extent;

#define GList_METHODS \
    GObj_METHODS \
    G_METHOD(int, isEmpty)(); \
    G_METHOD(int, length)(); \
    G_METHOD(void *, push)(void *ptr); \
    G_METHOD(void *, pop)(void); \
    G_METHOD(void *, insert)(int n, void *); \
    G_METHOD(void *, get)(int n); \
    G_METHOD(void *, set)(int n, void *ptr); \
    G_METHOD(void *, remove)(int n); \

// class structs

typedef struct GListClass {
    GObjClass *super;
    GObjStatics *statics;
    GList_METHODS
} GListClass;

typedef struct GList {
    GListClass *class;
    GList_MEMBERS
} GList;

// constructors
extern GList *GList_new(void);
extern GList *GList_new_full(Goop *this, char *name, int max, int extent);

// class init
extern GListClass *GListClass_init(char *name, GListClass *class);

#endif // __GList__