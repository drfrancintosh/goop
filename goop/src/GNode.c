#include "GNode.h"

/* *** OVERRIDES  *** */
// none

/* *** local / private functions *** */
static inline bool __isOnlyChild(GNode *sibling) {
    return (sibling->prev == NULL) && (sibling->next == NULL);
}

/* *** CLASS METHODS *** */
static void *addNext(GNode *sibling) {
    // adds "sibling" as the next child of *this*
    // returns the "next" sibling if there was one (NULL otherwise)
    GNode *this = _THAT_;
    if (!__isOnlyChild(sibling)) return $(this)->throw("add: '%s' must nave no siblings", sibling->name);
    GNode *next = this->next;
    this->next = sibling;
    if (next) next->prev = sibling;
    sibling->prev = this;
    sibling->next = next;
    return next;
}

static void *addPrev(GNode *sibling) {
    // adds the "sibling" as the prev child of *this*
    // returns the "prev" sibling if there was one (NULL otherwise)
    GNode *this = _THAT_;
    if (this->prev) return _(this->prev)->addNext(sibling);
    if (!__isOnlyChild(sibling)) return $(this)->throw("add: node(%s) must nave no siblings", sibling->name);
    this->prev = sibling;
    sibling->next = this;
    return NULL;
}

static void *getHead(void) {
    // returns the "head" of list of nodes
    GNode *this = _THAT_;
    GNode *head = this;
    while(head->prev) head = head->prev;
    return head;
}

static void *getTail(void) {
    // returns the "tail" of list of nodes
    GNode *this = _THAT_;
    GNode *tail = this;
    while(tail->next) tail = tail->next;
    return tail;
}

// NOTE: must be named _remove so as not to clash with stdio(remove)
static void *_remove(void) {
    // removes *this* from linked list
    // if removed, *this* is returned
    // if not removed (it was already an only child) NULL is returned
    GNode *this = _THAT_;
    if (__isOnlyChild(this)) return NULL;
    GNode *prev = this->prev;
    GNode *next = this->next;
    if (prev) prev->next = next;
    if (next) next->prev = prev;
    this->prev = NULL;
    this->next = NULL;
    return this;
}

/* *** CLASS INITIALIZATION *** */
static GNodeClass _class;
GNodeClass *GNodeClass_init( char *name, GNodeClass *class) {
    if (class->super) return &_class;
    class->super = GObjClass_init(name, (GObjClass *)class);
    class->_instanceSize = sizeof(GNode);
    // class methods...
    class->addNext = addNext;
    class->addPrev = addPrev;
    class->remove = _remove;
    class->getHead = getHead;
    class->getTail = getTail;
    return &_class;
}

/* *** CONSTRUCTORS *** */
GNode *GNode_new_full(Goop *_this, char *name) {
    G_CAST(GNode, this, _this);
    GNodeClass *class = GNodeClass_init("GNode", &_class);
    if (!this) this = class->alloc(class);
    GObj_new_full((GObj *)this, name);
    this->class = class;
    // instance members...
    return this;
}

GNode *GNode_new(void) {
    return GNode_new_full(NULL, "GNode");
}