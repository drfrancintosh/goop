#include "Goop.h"
#include <time.h>

void *_THAT_; // Global variable to store the current object
void *Goop_ERROR = (void *) -1;
int Goop_IERROR = -1;

bool goop_equals(void *a, void *b) {
    G_DEBUG("goop_equals: a=%p b=%p\n", a, b);
    if (a == b || a == NULL || b == NULL) return a == b;
    G_DEBUG("goop_equals: a=%s b=%s\n", a, b);
    return strcmp(a,b) == 0;
}