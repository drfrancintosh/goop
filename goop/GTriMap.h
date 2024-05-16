#ifndef __GTriMap__
#define __GTriMap__

#include "GMap.h"

// forward references 
G_FORWARD(GTriMap)

// constants

// members & methods
#define GTriMap_MEMBERS \
    GMap_MEMBERS \
    void *oldType; \
    GList *types; \

#define GTriMap_METHODS \
    GMap_METHODS \
    G_METHOD(void **, triPut)(char *key, void *value, void *type); \
    G_METHOD(void **, triGet)(char *key); \
    G_METHOD(void **, itriGet)(int n); \

// class structs
typedef struct GTriMapClass {
    GMapClass *super;
    GObjStatics *statics;
    GTriMap_METHODS
} GTriMapClass;

typedef struct GTriMap {
    GTriMapClass *class;
    GTriMap_MEMBERS
} GTriMap;

// constructors
extern GTriMap *GTriMap_new(void);
extern GTriMap *GTriMap_new_full(Goop *this, char *name, int max, int extent);

// class init
extern GTriMapClass *GTriMapClass_init(char *name, GTriMapClass *class);

// satisfy forward references

#endif // __GTriMap__