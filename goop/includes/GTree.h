#ifndef __GTree__
#define __GTree__

#include "GNode.h"

// forward references 
G_FORWARD(GTree);

// constants

// members & methods
#define GTree_MEMBERS \
    GNode_MEMBERS \
    GTree *parent; \
    GTree *children; \

#define GTree_METHODS \
    GNode_METHODS \
    G_METHOD(void *, addChildren)(GTree *children); \
    G_METHOD(void *, addHeadChildren)(GTree *children); \

// class structs
typedef struct GTreeClass {
    GNodeClass *super;
    GObjStatics *statics;
    GTree_METHODS
} GTreeClass;

typedef struct GTree {
    GTreeClass *class;
    GTree_MEMBERS
} GTree;

// constructors
extern GTree *GTree_new(void);
extern GTree *GTree_new_full(Goop *this, char *name);

// class init
extern GTreeClass *GTreeClass_init(char *name, GTreeClass *class);

#endif // __GTree__