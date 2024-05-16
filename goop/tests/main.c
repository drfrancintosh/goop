#include "tests.h"

int main()
{
    printf("Hello World\n");
    GObj_tests();
    GQueue_tests();
    GMap_tests();
    GNode_tests();
    GList_tests(); // final test exits app (run this last)
}
