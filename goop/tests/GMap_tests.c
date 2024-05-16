#include "tests.h"
#include <stdarg.h>

static void test_default_constructor() {
    printf("...test_default_constructor\n");
    GMap *map = GMap_new();
    _(map)->put("one", "UNO");
    void *foo = _(map)->get("one");
    assert(G_EQUALS(foo, "UNO"));
}

static void test_multiple_puts_gets() {
    printf("...test_multiple_puts_gets\n");
    GMap *map = GMap_new_full(NULL, "GMAP_test", 8, 8);
    char key[100];
    char value[100];
    printf("......add 100 items\n");
    for (int i = 0; i < 100; i++) {
        sprintf(key, "key[%d]", i);
        sprintf(value, "value[%d]", i);
        _(map)->put(strdup(key), strdup(value));
    }
    printf("......find 100 items\n");
    for (int i = 0; i < 100; i++) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->get(key);
        sprintf(value, "value[%d]", i);
        assert(G_EQUALS(val, value));
    }
}

static void test_removes() {
    printf("...test_removes\n");
    GMap *map = GMap_new_full(NULL, "GMAP_test", 8, 8);
    char key[100];
    char value[100];
    printf("......add 100 items\n");
    for (int i = 0; i < 100; i++) {
        sprintf(key, "key[%d]", i);
        sprintf(value, "value[%d]", i);
        _(map)->put(strdup(key), strdup(value));
    }
    printf("......remove even items\n");
    for (int i = 0; i < 100; i += 2) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->remove(key);
        sprintf(value, "value[%d]", i);
        assert(G_EQUALS(val, value));
    }
    printf("......verify even items removed\n");
    for (int i = 0; i < 100; i += 2) {
        // find the evens
        sprintf(key, "key[%d]", i);
        char *val = _(map)->get(key);
        assert(val == NULL);
    }
    printf("......find odd items\n");
    for (int i = 1; i < 100; i += 2) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->get(key);
        sprintf(value, "value[%d]", i);
        assert(G_EQUALS(val, value));
    }
    printf("......try to remove even items again\n");
    for (int i = 0; i < 100; i += 2) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->remove(key);
        sprintf(value, "value[%d]", i);
        // if (val == Goop_ERROR) printf("key=%s, value=Goop_ERROR\n", key);
        // else printf("key=%s value=%s\n", key, val);
        assert(val == Goop_ERROR);
    }
    printf("......remove remaining odd items\n");
    for (int i = 1; i < 100; i += 2) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->remove(key);
        sprintf(value, "value[%d]", i);
        // if (val == Goop_ERROR) printf("key=%s, value=Goop_ERROR\n", key);
        // else printf("key=%s value=%s\n", key, val);
        assert(G_EQUALS(val, value));
    }
    printf("......verify all items removed\n");
    for (int i = 0; i < 100; i += 1) {
        // find the evens
        sprintf(key, "key[%d]", i);
        char *val = _(map)->get(key);
        assert(val == NULL);
    }
}

static void test_findKey_iget(void) {
    printf("...test_findKey_iget\n");
    GMap *map = GMap_new_full(NULL, "GMAP_test", 8, 8);
    char key[100];
    char value[100];
    printf("......add 100 items\n");
    for (int i = 0; i < 100; i++) {
        sprintf(key, "key[%d]", i);
        sprintf(value, "value[%d]", i);
        _(map)->put(strdup(key), strdup(value));
    }
    printf("......remove even items\n");
    for (int i = 0; i < 100; i += 2) {
        sprintf(key, "key[%d]", i);
        char *val = _(map)->remove(key);
        sprintf(value, "value[%d]", i);
        assert(G_EQUALS(val, value));
    }
    printf("......find all items by slot number\n");
    for (int i = 0; i < 100; i += 1) {
        sprintf(key, "key[%d]", i);
        int n = _(map)->findKey(key);
        sprintf(value, "value[%d]", i);
        char *val = _(map)->iget(n);
        if (i%2 == 0) assert(G_EQUALS(val, NULL));
        else assert(G_EQUALS(val, value));
    }
}

void GMap_tests(void) {
    printf("GMap_tests\n");
    test_default_constructor();
    test_multiple_puts_gets();
    test_removes();
    test_findKey_iget();
}