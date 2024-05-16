#ifndef __GQueue__
#define __GQueue__

#include "GObj.h"

// forward references 

// constants

// members & methods
#define GQueue_MEMBERS \
    GObj_MEMBERS \
    void **list; \
    int head; \
    int tail; \
    int max; \
    bool overwrite; \

#define GQueue_METHODS \
    GObj_METHODS \
    G_METHOD(bool, isEmpty)(void); \
    G_METHOD(bool, isFull)(void); \
    G_METHOD(void *, push)(void *ptr); \
    G_METHOD(void *, pop)(void); \
    G_METHOD(void *, pull)(void); \

// class structs
typedef struct GQueueClass {
    GObjClass *super;
    GObjStatics *statics;
    GQueue_METHODS
} GQueueClass;

typedef struct GQueue {
    GQueueClass *class;
    GQueue_MEMBERS
} GQueue;

// constructors
extern GQueue *GQueue_new(void);
extern GQueue *GQueue_new_full(Goop *this, char *name, int max);

// class init
extern GQueueClass *GQueueClass_init(char *name, GQueueClass *class);

#endif // __GQueue__