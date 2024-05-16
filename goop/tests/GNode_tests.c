#include "tests.h"

static void test_next_inserts() {
    printf("...test_next_inserts\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(third);
    _(first)->addNext(second);
    for(GNode *n = first; n; n = n->next) {
        printf("......node(%s)\n", n->name);
    }
    for(GNode *p = third; p; p = p->prev) {
        printf("......node(%s)\n", p->name);
    }
    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, second));
    assert(G_EQUALS(first->prev, NULL));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, third));
    assert(G_EQUALS(second->prev, first));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, NULL));
    assert(G_EQUALS(third->prev, second));
}

static void test_prev_inserts() {
    printf("...test_prev_inserts\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addPrev(third);
    _(first)->addPrev(second);
    for(GNode *n = third; n; n = n->next) {
        printf("......node(%s)\n", n->name);
    }
    for(GNode *p = first; p; p = p->prev) {
        printf("......xnode(%s)\n", p->name);
    }
    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, NULL));
    assert(G_EQUALS(first->prev, second));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, first));
    assert(G_EQUALS(second->prev, third));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, second));
    assert(G_EQUALS(third->prev, NULL));
}

static void test_remove_middle() {
    printf("...test_remove_middle\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(third);
    _(first)->addNext(second);
    _(second)->remove();

    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, third));
    assert(G_EQUALS(first->prev, NULL));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, NULL));
    assert(G_EQUALS(second->prev, NULL));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, NULL));
    assert(G_EQUALS(third->prev, first));
}

static void test_circular_reference() {
    printf("...test_circular_reference\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(third);
    GNode *next = _(third)->addNext(first);

    assert(G_EQUALS(next, Goop_ERROR));

    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, third));
    assert(G_EQUALS(first->prev, NULL));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, NULL));
    assert(G_EQUALS(second->prev, NULL));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, NULL));
    assert(G_EQUALS(third->prev, first));
}

static void test_remove_head() {
    printf("...test_remove_head\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(second);
    _(second)->addNext(third);
    _(first)->remove();

    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, NULL));
    assert(G_EQUALS(first->prev, NULL));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, third));
    assert(G_EQUALS(second->prev, NULL));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, NULL));
    assert(G_EQUALS(third->prev, second));
}

static void test_remove_tail() {
    printf("...test_remove_tail\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(second);
    _(third)->addNext(third);
    _(third)->remove();

    assert(G_EQUALS(first->name, "first"));
    assert(G_EQUALS(first->next, second));
    assert(G_EQUALS(first->prev, NULL));

    assert(G_EQUALS(second->name, "second"));
    assert(G_EQUALS(second->next, NULL));
    assert(G_EQUALS(second->prev, first));

    assert(G_EQUALS(third->name, "third"));
    assert(G_EQUALS(third->next, NULL));
    assert(G_EQUALS(third->prev, NULL));
}

static void test_find_head_tail() {
    printf("...test_find_head\n");
    GNode *first = GNode_new_full(NULL, "first");
    GNode *second = GNode_new_full(NULL, "second");
    GNode *third = GNode_new_full(NULL, "third");
    _(first)->addNext(second);
    _(second)->addNext(third);
    GNode *head = _(third)->getHead();
    GNode *tail = _(head)->getTail();

    assert(G_EQUALS(head, first));
    assert(G_EQUALS(tail, third));

    _(second)->remove();
    head = _(second)->getHead();
    tail = _(second)->getTail();
    assert(G_EQUALS(head, second));
    assert(G_EQUALS(tail, second));

}

void GNode_tests(void) {
    printf("GNode_tests\n");
    test_next_inserts();
    test_prev_inserts();
    test_remove_middle();
    test_remove_head();
    test_remove_tail();
    test_circular_reference();
    test_find_head_tail();
}