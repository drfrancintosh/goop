#include "tests.h"

static void quiet_throws() {
    printf("...quiet_throws\n");
    GQueue *list = GQueue_new();
    list->class->flags |= GObjClass_FLAG_QUIET_ON_THROW;
    _(list)->destroy();
}
static void test_push_pop() {
    printf("...test_push_pop\n");
    GQueue *list = GQueue_new_full(NULL, "test_push_pop", 2);
    _(list)->push("Hello");
    _(list)->push("Greg");
    assert(list->head == 0);
    assert(list->tail == 0);
    assert(list->list[list->head] != 0);
    assert(_(list)->isFull());
    void *greg = _(list)->pop();
    void *hello = _(list)->pop();
    assert(G_EQUALS(greg, "Greg"));
    assert(G_EQUALS(hello, "Hello"));
    assert(list->head == 0);
    assert(list->tail == 0);
    assert(list->list[list->head]== 0);
    void *ptr = _(list)->pop();
    assert(ptr == Goop_ERROR);
}

static void test_push_pull() {
    printf("...test_push_pull\n");
    GQueue *list = GQueue_new_full(NULL, "test_push_pop", 2);
    _(list)->push("Hello");
    _(list)->push("Greg");
    assert(list->head == 0);
    assert(list->tail == 0);
    assert(list->list[list->head] != 0);
    assert(_(list)->isFull());
    void *hello = _(list)->pull();
    void *greg = _(list)->pull();
    assert(G_EQUALS(greg, "Greg"));
    assert(G_EQUALS(hello, "Hello"));
    assert(list->head == 0);
    assert(list->tail == 0);
    assert(list->list[list->head]== 0);
    void *ptr = _(list)->pull();
    assert(ptr == Goop_ERROR);
}
// static void test_extent() {
//     printf("...test_extent\n");
//     GQueue *list = GQueue_new();
//     for (int i = 0; i < 20; i++) {
//         _(list)->push("word");
//     }
//     assert(list->length == 20);
//     assert(list->max == 24);
//     assert(list->extent == 8);
// }

// static void test_push_pop() {
//     printf("...test_push_pop\n");
//     GQueue *list = GQueue_new();
//     char buff[100];
//     int n = 40;
//     int max = ((n - 1) / 8 + 1) * 8;
//     for (int i = 0; i < n; i++) {
//         sprintf(buff, "word[%d]", i);
//         _(list)->push(strdup(buff));
//         // printf("%d: %s\n", i, buff);
//         // printf("list: %d\n", list->length);
//     }
//     assert(list->length == n);
//     // printf("max=%d %d\n", max, list->max);
//     assert(list->max == max);
//     assert(list->extent == 8);
//     for (int i = n - 1; i >= 0; i--) {
//         sprintf(buff, "word[%d]", i);
//         char *word = _(list)->pop();
//         // printf("buff: %d: %s\n", i, buff);
//         // printf("obj:  %d: %s\n", i, word);
//         assert(G_EQUALS(buff, word));
//     }
// }

// void test_exception() {
//     printf("...test_exception\n");
//     printf("[EXCEPTION EXPECTED]\n");
//     GQueue *list = GQueue_new_full(NULL, "test_exception", 8, 8);
//     list->class->flags |= GObjClass_FLAG_DIE_ON_THROW; // exits the app on error
//     void *ptr = _(list)->pop();
//     assert(ptr == Goop_ERROR);
//     printf("[EXCEPTION EXPECTED]\n");
// }

// void test_isEmpty() {
//     printf("...test_isEmpty\n");
//     GQueue *list = GQueue_new();
//     _(list)->insert(0, "hello");
//     assert(_(list)->isEmpty() == 0);
//     char *s = _(list)->delete (0);
//     assert(G_EQUALS(s, "hello"));
//     assert(_(list)->isEmpty());
// }
// void test_length() {
//     printf("...test_length\n");
//     GQueue *list = GQueue_new();
//     _(list)->insert(0, "hello");
//     assert(_(list)->length() == 1);
//     char *s = _(list)->delete (0);
//     assert(G_EQUALS(s, "hello"));
//     assert(_(list)->length() == 0);
// }

// void test_get() {
//     printf("...test_get\n");
//     GQueue *list = GQueue_new();
//     _(list)->insert(0, "hello");
//     _(list)->insert(1, "world");
//     assert(G_EQUALS(_(list)->get(0), "hello"));
//     assert(G_EQUALS(_(list)->get(1), "world"));
//     assert(_(list)->get(2) == Goop_ERROR); // throws exception
// }

// void test_set() {
//     printf("...test_set\n");
//     GQueue *list = GQueue_new();
//     _(list)->insert(0, "hello");
//     _(list)->insert(1, "world");
//     _(list)->set(0, "greg");
//     _(list)->set(1, "smith");
//     assert(G_EQUALS(_(list)->get(0), "greg"));
//     assert(G_EQUALS(_(list)->get(1), "smith"));
//     assert(_(list)->set(2, "error") == Goop_ERROR); // throws exception
// }

void GQueue_tests(void) {
    printf("GQueue_tests\n");
    quiet_throws();
    test_push_pop();
    test_push_pull();
    // test_extent();
    // test_push_pop();
    // test_isEmpty();
    // test_length();
    // test_get();
    // test_set();
    // test_exception(); // exits appp
}