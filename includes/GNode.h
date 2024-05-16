#ifndef __GNode__
#define __GNode__

#include "GObj.h"

// forward references 
G_FORWARD(GNode);

// constants

// members & methods
#define GNode_MEMBERS \
    GObj_MEMBERS \
    GNode *next; \
    GNode *prev; \

#define GNode_METHODS \
    GObj_METHODS \
    G_METHOD(void *, addNext)(GNode *sibling); \
    G_METHOD(void *, addPrev)(GNode *sibling); \
    G_METHOD(void *, remove)(void); \
    G_METHOD(void *, getHead)(void); \
    G_METHOD(void *, getTail)(void); \

// class structs
typedef struct GNodeClass {
    GObjClass *super;
    GObjStatics *statics;
    GNode_METHODS
} GNodeClass;

typedef struct GNode {
    GNodeClass *class;
    GNode_MEMBERS
} GNode;

// constructors
extern GNode *GNode_new(void);
extern GNode *GNode_new_full(Goop *this, char *name);

// class init
extern GNodeClass *GNodeClass_init(char *name, GNodeClass *class);

#endif // __GNode__