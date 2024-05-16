#include "tests.h"

static void quiet_throws() {
    printf("...quiet_throws\n");
    GList *list = GList_new();
    list->class->flags |= GObjClass_FLAG_QUIET_ON_THROW;
    _(list)->destroy();
}
static void test_push() {
    printf("...test_push\n");
    char buff[100];
    GList *list = GList_new();
    _(list)->push("Hello");
    _(list)->push("Greg");
    assert(list->length == 2);
    sprintf(buff, "%s %s\n", _(list)->pop(), _(list)->pop());
    // printf("%s\n", buff);
    assert(list->length == 0);
}

static void test_extent() {
    printf("...test_extent\n");
    GList *list = GList_new();
    for (int i = 0; i < 20; i++) {
        _(list)->push("word");
    }
    assert(list->length == 20);
    assert(list->max == 24);
    assert(list->extent == 8);
}

static void test_push_pop() {
    printf("...test_push_pop\n");
    GList *list = GList_new();
    char buff[100];
    int n = 40;
    int max = ((n - 1) / 8 + 1) * 8;
    for (int i = 0; i < n; i++) {
        sprintf(buff, "word[%d]", i);
        _(list)->push(strdup(buff));
        // printf("%d: %s\n", i, buff);
        // printf("list: %d\n", list->length);
    }
    assert(list->length == n);
    // printf("max=%d %d\n", max, list->max);
    assert(list->max == max);
    assert(list->extent == 8);
    for (int i = n - 1; i >= 0; i--) {
        sprintf(buff, "word[%d]", i);
        char *word = _(list)->pop();
        // printf("buff: %d: %s\n", i, buff);
        // printf("obj:  %d: %s\n", i, word);
        assert(G_EQUALS(buff, word));
    }
}

void test_exception() {
    printf("...test_exception\n");
    printf("[EXCEPTION EXPECTED]\n");
    GList *list = GList_new_full(NULL, "test_exception", 8, 8);
    list->class->flags |= GObjClass_FLAG_DIE_ON_THROW; // exits the app on error
    void *ptr = _(list)->pop();
    assert(ptr == Goop_ERROR);
    printf("[EXCEPTION EXPECTED]\n");
}

void test_isEmpty() {
    printf("...test_isEmpty\n");
    GList *list = GList_new();
    _(list)->insert(0, "hello");
    assert(_(list)->isEmpty() == 0);
    char *s = _(list)->remove (0);
    assert(G_EQUALS(s, "hello"));
    assert(_(list)->isEmpty());
}
void test_length() {
    printf("...test_length\n");
    GList *list = GList_new();
    _(list)->insert(0, "hello");
    assert(_(list)->length() == 1);
    char *s = _(list)->remove (0);
    assert(G_EQUALS(s, "hello"));
    assert(_(list)->length() == 0);
}

void test_get() {
    printf("...test_get\n");
    GList *list = GList_new();
    _(list)->insert(0, "hello");
    _(list)->insert(1, "world");
    assert(G_EQUALS(_(list)->get(0), "hello"));
    assert(G_EQUALS(_(list)->get(1), "world"));
    assert(_(list)->get(2) == Goop_ERROR); // throws exception
}

void test_set() {
    printf("...test_set\n");
    GList *list = GList_new();
    _(list)->insert(0, "hello");
    _(list)->insert(1, "world");
    _(list)->set(0, "greg");
    _(list)->set(1, "smith");
    assert(G_EQUALS(_(list)->get(0), "greg"));
    assert(G_EQUALS(_(list)->get(1), "smith"));
    assert(_(list)->set(2, "error") == Goop_ERROR); // throws exception
}

void GList_tests(void) {
    printf("GList_tests\n");
    quiet_throws();
    test_push();
    test_extent();
    test_push_pop();
    test_isEmpty();
    test_length();
    test_get();
    test_set();
    test_exception(); // exits appp
}