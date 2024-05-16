#include "GMap.h"
#include "GList.h"

/* *** OVERRIDES  *** */
// none

/* *** CLASS METHODS *** */
// none

static int _lastNull = 0;
static int findKey(char *key) {
    // returns index if key is found in list
    // returns 0 if not found
    // actually, entry 0 in the map is RESERVED
    // there may be NULL entries in the keys list due to removals
    // _lastNull is set to the last NULL entry found during the search
    GMap *this = _THAT_;
    _lastNull = 0;
    if (key == NULL) return 0; // NULL keys are not searchable
    // we start the search at '1' because slot[0] is RESERVED
    for (int i = 1; i < this->keys->length; i++) {
        char *testKey = this->keys->list[i];
        if (testKey == NULL) {
            _lastNull = i;
        }  else if (G_EQUALS(testKey, key)) {
            return i;
        }
    }
    return 0;
}

static void *put(char *key, void *value) {
    // puts the value into the map at the key
    // returns the old value, if there was one
    // returns NULL otherwise
    // NOTE: value can be NULL, but it is a very bad idea
    // NOTE: because returning a NULL value indicates it was not found
    GMap *this = _THAT_;
    this->oldKey = NULL;
    this->oldValue = NULL;
    int n = _(this)->findKey(key);
    if (n) {
        // replace old value with new value
        this->oldKey = _(this->keys)->get(n);
        this->oldValue = _(this->values)->get(n);
        _(this->values)->set(n, value);
    } else if (_lastNull) {
        // replace NULL entry with new key and value
        this->oldKey = _(this->keys)->get(_lastNull);
        this->oldValue = _(this->values)->get(_lastNull);
        _(this->keys)->set(_lastNull, key);
        _(this->values)->set(_lastNull, value);
    } else {
        // add new key and value to the end of the lists
        _(this->keys)->push(key);
        _(this->values)->push(value);
    }
    // return the old value so it can be destroyed if necessary
    // the old key is in this->oldKey so it can be "freed" if necessary
    // if this->oldValue is NULL, then the key was not found
    return this->oldValue;
}

static void *get(char *key) {
    // retrieves a key based on the key 
    // returns NULL if the key is not found
    GMap *this = _THAT_;
    int n = _(this)->findKey(key);
    return _(this)->iget(n);
}

static void *iget(int n) {
    // lookup value by "slot"
    // slot[0] is RESERVED
    // selecting a slot that is out of the array bounds is an ERROR
    // a NULL will be returned if the key was not found
    GMap *this = _THAT_;
    void *value = _(this->values)->get(n);
    // if value is NULL, then the key was not found
    return value;
}

// NOTE: must be named _remove not to conflict with stdio.h
static void *_remove(char *key) {
    GMap *this = _THAT_;
    this->oldKey = NULL;
    this->oldValue = Goop_ERROR; // it's an error to remove an item not in the map
    int n = _(this)->findKey(key);
    if (n) {
        // replace old value with new value
        this->oldKey = _(this->keys)->get(n);
        this->oldValue = _(this->values)->get(n);
        _(this->keys)->set(n, NULL);
        _(this->values)->set(n, NULL);
    }
    // return the old value so it can be destroyed if necessary
    // the old key is in this->oldKey so it can be "freed" if necessary
    // if this->oldValue is NULL, then the key was not found
    return this->oldValue;
}

/* *** local / private functions *** */
// none

/* *** CLASS INITIALIZATION *** */
static GMapClass _class;
GMapClass *GMapClass_init(char *name, GMapClass *class) {
    if (class->super) return &_class;
    class->super = GObjClass_init(name, (GObjClass *)class);
    class->_instanceSize = sizeof(GMap);
    // class methods...
    class->findKey = findKey;
    class->iget = iget;
    class->get = get;
    class->put = put;
    class->remove = _remove;
    // overrides...
    return &_class;
}

/* *** CONSTRUCTORS *** */
GMap *GMap_new_full(Goop *_this, char *name, int max, int extent) {
    G_CAST(GMap, this, _this);
    GMapClass *class = GMapClass_init("GMap", &_class);
    if (!this) this = class->alloc(class);
    GObj_new_full(this, name);
    this->class = class;
    // instance members...
    this->keys = GList_new_full(NULL, "keys", max, extent);
    this->values = GList_new_full(NULL, "values", max, extent);
    // entry 0 is RESERVED (so that findKey always returns a non-zero integer)
    _(this->keys)->push(NULL);
    _(this->values)->push(NULL);
    return this;
}

GMap *GMap_new(void) {
    return GMap_new_full(NULL, "GMap", 8, 8);
}