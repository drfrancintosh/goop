#include "tests.h"
#include <stdarg.h>

void test_alloc_one() {
    printf("...test_alloc_one\n");
    GObj *one;
    one = GObj_new();
    _(one)->destroy();
    GObj *two = GObj_new();
    // printf("%p: %s\n", two, two->name);
    assert(one == two);
}

void test_alloc_ten() {
    printf("...test_alloc_ten\n");
    GObj *arr[10];
    char buff[100];
    // allocate 10 objects
    for (int i = 0; i < 10; i++) {
        sprintf(buff, "obj[%d]", i);
        arr[i] = GObj_new_full(NULL, strdup(buff));
        printf("%d: %p: %s\n", i, arr[i], arr[i]->name);
    }
    // free them and observe they are on the freelist
    for (int i = 0; i < 10; i++) {
        void *oldFreelist = arr[i]->class->_freelist;
        _(arr[i])->destroy();
        printf("destroy: %d: (oldFreelist=%p) freelist=%p, arr[i]=%p: name=%s, arr->userdata=%p\n", 
        i, oldFreelist, arr[i]->class->_freelist, arr[i], arr[i]->name, arr[i]->userdata);
        assert(arr[i]->class->_freelist == arr[i]);
        assert(arr[i]->userdata == oldFreelist);
    }
    // reallocate them (in reverse order) and get the same objects back
    for (int i = 9; i >= 0; i--) {
        sprintf(buff, "obj[%d]", i);
        GObj *obj = GObj_new_full(NULL, strdup(buff));
        printf("%d: %p: %s, %p: %s\n", i, obj, obj->name, arr[i], arr[i]->name);
        assert(arr[i] == obj);
        assert(arr[i]->flags == 0);
    }
    // free the same object twice
    _(arr[0])->destroy();
    assert(arr[0]->class->_freelist == arr[0]);
    assert(arr[0]->flags & GObj_FLAG_DESTROYED);
    _(arr[0])->destroy();
    assert(arr[0]->class->_freelist == arr[0]);
}

void test_alloc_ten_default_constructor() {
    printf("...test_alloc_ten_default_constructor\n");
    GObj *arr[10];
    char buff[100];
    // allocate 10 objects
    for (int i = 0; i < 10; i++) {
        sprintf(buff, "obj[%d]", i);
        arr[i] = GObj_new();
        // printf("%p: %s\n", arr[i], arr[i]->name);
    }
    // free them and observe they are on the freelist
    for (int i = 0; i < 10; i++) {
        _(arr[i])->destroy();
        // printf("%d: %d\n", i, arr[9]->class->_freelist->length);
        assert(arr[i]->class->_freelist == arr[i]);
    }
    // reallocate them (in reverse order) and get the same objects back
    for (int i = 9; i >= 0; i--) {
        sprintf(buff, "obj[%d]", i);
        GObj *obj = GObj_new();
        // printf("%p: %s\n", obj, obj->name);
        assert(arr[i] == obj);
    }
}

void test_format() {
    printf("...test_format\n");
    GObj *obj = GObj_new();
    char *msg = $(obj)->format("here's a test: %d", 42);
    assert(G_EQUALS(msg, "here's a test: 42"));
}

void test_vformat(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("...test_vformat\n");
    GObj *obj = GObj_new();
    char *msg = $(obj)->vformat(fmt, args);
    assert(G_EQUALS(msg, "here's a test: 42"));
    va_end(args);
}

static void test_msNow() {
    printf("...test_msNow\n");
    GObj *obj = GObj_new();
    uint64_t now = $(obj)->msNow();
    printf("%d\n", now);
    assert(now != 0);
}

void GObj_tests(void) {
    printf("GObj_tests\n");
    test_alloc_one();
    test_alloc_ten();
    test_alloc_ten_default_constructor();
    test_format();
    test_vformat("here's a test: %d", 42);
    test_msNow();
}