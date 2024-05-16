#include "GQueue.h"

/**
 ** GQueue
 ** Simple circular queue
 **   - push (always pushes on the head of the queue)
 **   - pull (always pulls from the tail of the queue - FILO)
 **   - pop (always pops from the head of the queue - FIFO)
 ** no extensions 
 ** NULL pointers indicate free location
 ** this->head points to the next available space (almost always NULL)
 ** this->tail points to the oldest item to be removed (first in list)
 ** if this->head == this->tail, the queue is empty or full
 **   - if entry is NULL, the queue is empty
 **   - if entry is not NULL, the queue is full 
 **  - Arguably, if this-list[this->head] is not NULL, the queue is full
 **/

/* *** local / private functions *** */

static int inline __next(GQueue *this, int n) {
    return (n + 1) % this->max;
}

static int inline __prev(GQueue *this, int n) {
    return (n + this->max - 1) % this->max;
}


/* *** OVERRIDES  *** */
static void _debug(char *msg, ...) {
    GQueue *this = _THAT_;
    G_PRINTF("%s(%s): %s\n", this->class->name, this->name, msg);
    G_PRINTF("...head: %d\n", this->head);
    G_PRINTF("...max: %d\n", this->max);
    for (int i = 0; i < this->head; i++) {
        G_PRINTF("...list[%d]: %s\n", i, this->list[i]);
    }
}

/* *** CLASS METHODS *** */
static bool isFull() {
    GQueue *this = _THAT_;
    return (this->head == this->tail) && (this->list[this->head] != NULL);
}

static bool isEmpty() {
    GQueue *this = _THAT_;
    return (this->head == this->tail) && (this->list[this->head] == NULL);
}

static void *push(void *ptr) {
    GQueue *this = _THAT_;
    if (ptr == NULL) return $(this)->throw("ERROR: push(NULL) is illegal");
    GObj *headObj = this->list[this->head];
    if (headObj != NULL) {
        // head is not empty - overwrite and possibly destroy
        if (this->overwrite) {
            GObj *tailObj = _(this)->pull();
            if (tailObj->flags & GObj_FLAG_AUTODESTROY) _(tailObj)->destroy();
        } else {
            return $(this)->throw("ERROR: push(head=%d, tail=%d): queue is full", this->head, this->tail);
        }
    }
    this->list[this->head] = ptr;
    this->head = __next(this, this->head);
    return ptr;
}

static void *pull(void) {
    GQueue *this = _THAT_;
    GObj *tailObj = this->list[this->tail];
    if (tailObj == NULL) {
        return $(this)->throw("'ERROR: pull(tail=%d, max=%d) queue empty (tail points to NULL)", this->tail, this->max);
    }
    this->list[this->tail] = NULL;
    this->tail = __next(this, this->tail);
    return tailObj;
}

static void *pop(void) {
    GQueue *this = _THAT_;
    if (_(this)->isEmpty()) return $(this)->throw("'ERROR: pop(head=%d, tail=%d) queue empty", this->head, this->tail);
    int prev = __prev(this, this->head);
    GObj *prevObj = this->list[prev];
    this->list[prev] = NULL;
    this->head = prev;
    return prevObj;
}

/* *** CLASS INITIALIZATION *** */
static GQueueClass _class;
GQueueClass *GQueueClass_init(char *name, GQueueClass *class) {
    if (class->super) return &_class;
    class->super = GObjClass_init(name, (GObjClass *)class);
    class->_instanceSize = sizeof(GQueue);
    // class methods
    class->push = push;
    class->pull = pull;
    class->pop = pop;
    class->isFull = isFull;
    class->isEmpty = isEmpty;
    // overrides...
    class->debug = _debug; // override
    return &_class;
}

/* *** CONSTRUCTORS *** */
GQueue *GQueue_new_full(Goop *_this, char *name, int max) {
    G_CAST(GQueue, this, _this);
    GQueueClass *class = GQueueClass_init("GQueue", &_class);
    if (!this) this = class->alloc(class);
    GObj_new_full(this, name);
    this->class = class;
    this->max = max;
    this->head = 0;
    this->list = G_CALLOC(this->max, void *);
    return this;
}

GQueue *GQueue_new(void) {
    return GQueue_new_full(NULL, "GQueue", 8);
}