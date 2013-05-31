#include "testcases.h"

int main() {

    TestFixture t;
    ListTestConsecutiveInsert<ArrayList> arr_altci(1000, &t);
    ListTestModification<ArrayList> arr_altm(100, &t);
    ListTestRepetitiveClear<ArrayList> arr_altpc(100, &t);
    ListTestInsertAndRemove<ArrayList> arr_altir(100, &t);
    ListTestIterator<ArrayList> arr_alti(&t);

    ListTestConsecutiveInsert<LinkedList> linked_altci(1000, &t);
    ListTestModification<LinkedList> linked_altm(100, &t);
    ListTestRepetitiveClear<LinkedList> linked_altpc(100, &t);
    ListTestInsertAndRemove<LinkedList> linked_altir(100, &t);
    ListTestIterator<LinkedList> linked_alti(&t); 

    if (t.test_all()) puts("All tests have finished without errors.");
    else return 1;
    return 0;
}

