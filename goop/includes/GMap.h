#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

// forward references 

// constants

// members & methods
#define GMap_MEMBERS \
    GObj_MEMBERS \
    GList *keys; \
    GList *values; \
    char *oldKey; \
    void *oldValue; \

#define GMap_METHODS \
    GObj_METHODS \
    G_METHOD(void *, put)(char *key, void *value); \
    G_METHOD(void *, get)(char *key); \
    G_METHOD(void *, iget)(int n); \
    G_METHOD(void *, remove)(char *key); \
    G_METHOD(int, findKey)(char *key); \

// class structs
typedef struct GMapClass {
    GObjClass *super;
    GObjStatics *statics;
    GMap_METHODS
} GMapClass;

typedef struct GMap {
    GMapClass *class;
    GMap_MEMBERS
} GMap;

// constructors
extern GMap *GMap_new(void);
extern GMap *GMap_new_full(Goop *this, char *name, int max, int extent);

// class init
extern GMapClass *GMapClass_init(char *name, GMapClass *class);

#endif // __GMap__