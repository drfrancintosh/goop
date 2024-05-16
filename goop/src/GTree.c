#include "GTree.h"

/* *** local / private functions *** */
static inline bool __isOrphan(GTree *child) {
    return (child->parent == NULL);
}

static void *__makeParent(GTree *this, GTree *children) {
    if (children->prev != NULL) return $(this)->throw("addChildren: child '%s' must be a 'head' child", children->name);
    for (GTree *node = children; node; node = (GTree *)node->next) {
        if (!__isOrphan(node)) return $(this)->throw("addChildren: child '%s' must nave no parent", node->name);
    }

    for (GTree *child = children; child; child = (GTree *)child->next) {
        child->parent = this;
    }
    return NULL;
}

/* *** OVERRIDES  *** */
static void *_addNext(GNode *_sibling) {
    // overrides GNode::addNext
    GTree *this = _THAT_;
    G_CAST(GTree, sibling, _sibling);
    sibling->parent = this->parent;
    return _(this)->super->addNext(_sibling);
    ;
}

static void *_addPrev(GNode *_sibling) {
    // overrides GNode::addPrev
    GTree *this = _THAT_;
    G_CAST(GTree, sibling, _sibling);
    sibling->parent = this->parent;
    return _(this)->super->addPrev(_sibling);
}

static void *_remove(void) {
    // removes *this* from tree
    // (unlinks parent, and prev and next siblings, keeps children)
    // if removed, *parent* is returned
    // if not removed (it was already orphaned) NULL is returned
    GTree *this = _THAT_;
    if (__isOrphan(this)) return NULL; // already removed from tree
    GTree *parent = this->parent;
    if (parent->children == this) {
        // this is the "head" child
        parent->children = (GTree *)this->next;
    }
    this->parent = NULL;      // make *this* an orphan
    _(this)->super->remove(); // super->remove from children list
    return parent;
}

/* *** CLASS METHODS *** */
static void *addChildren(GTree *children) {
    // adds list of children to end of parent's children list
    // all children must be "orphaned" or none are added
    // "child" must be the "head" (children->prev == NULL)
    GTree *this = _THAT_;
    if (__makeParent(this, children)) return Goop_ERROR; // exception was thrown

    if (this->children) {
        GTree *lastChild = _(this->children)->getTail();
        lastChild->next = (GNode *)children;
        children->prev = (GNode *)lastChild;
    } else {
        this->children = children;
    }
    return NULL;
}

static void *addHeadChildren(GTree *children) {
    // adds list of children to head of parent's children list
    // all children must be "orphaned" or none are added
    // "child" must be the "head" (children->prev == NULL)
    GTree *this = _THAT_;
    if (__makeParent(this, children)) return Goop_ERROR; // exception was thrown

    if (this->children) {
        GTree *lastChild = _(children)->getTail();
        lastChild->next = (GNode *)this->children;
        this->children = children;
    } else {
        this->children = children;
    }
    return NULL;
}

/* *** CLASS INITIALIZATION *** */
static GTreeClass _class;
GTreeClass *GTreeClass_init(char *name, GTreeClass *class) {
    if (class->super) return &_class;
    class->super = GNodeClass_init(name, (GNodeClass *)class);
    class->_instanceSize = sizeof(GTree);
    // class methods...
    class->addChildren = addChildren;
    class->addHeadChildren = addHeadChildren;
    // overrides...
    class->addNext = _addNext;
    class->addPrev = _addPrev;
    class->remove = _remove; 

    return &_class;
}

/* *** CONSTRUCTORS *** */
GTree *GTree_new_full(Goop *_this, char *name) {
    G_CAST(GTree, this, _this);
    GTreeClass *class = GTreeClass_init("GTree", &_class);
    if (!this) this = class->alloc(class);
    GNode_new_full(this, name);
    this->class = class;
    // instance members...
    return this;
}

GTree *GTree_new(void) {
    return GTree_new_full(NULL, "GTree");
}