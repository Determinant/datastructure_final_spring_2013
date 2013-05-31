/**
 * Copyright (C) 2013 Ted Yin <ted.sybil@gmail.com>
 * This file is part of Spring 2013 Final Project for Data Structure Class.
 * 
 * SFPDSC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SFPDSC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 *     along with SFPDSC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "testcases.h"

class HashInt {
public:
    static int hashCode(int obj) {
        return obj;
    }
};

int main() {

    TestFixture t;
    
    ListTestConsecutiveInsert<ArrayList<int> > 
        arr_altci("ArrayListConsecutiveInsert", 1000, &t);
    ListTestModification<ArrayList<int> > 
        arr_altm("ArrayListModification", 100, &t);
    ListTestRepetitiveClear<ArrayList<int> > 
        arr_altpc("ArrayListRepetitiveClear", 100, &t);
    ListTestInsertAndRemove<ArrayList<int> > 
        arr_altir("ArrayListInsertAndRemove", 100, &t);
    ListTestIterator<ArrayList<int> > 
        arr_alti("ArrayListIterator", &t);
    ListTestRandomOperation<ArrayList<int> > 
        arr_ro("ArrayListRandomOperation", 10000, &t);
    

    ListTestConsecutiveInsert<LinkedList<int> > 
        linked_altci("LinkedListCosecutiveInsert", 1000, &t);
    ListTestModification<LinkedList<int> > 
        linked_altm("LinkedListModification", 100, &t);
    ListTestRepetitiveClear<LinkedList<int> > 
        linked_altpc("LinkedListRepetitive", 100, &t);
    ListTestInsertAndRemove<LinkedList<int> > 
        linked_altir("LinkedListInsertAndRemove", 100, &t);
    ListTestIterator<LinkedList<int> > 
        linked_alti("LinkedListItertor", &t); 
    ListTestRandomOperation<LinkedList<int> > 
        linked_ro("LinkedRandomOperation", 10000, &t);

    MapTestAllRandomly<TreeMap<int, int> > 
        tree_all("TreeMapAllRandom", 100000, 10000000, &t);
    MapTestAllRandomly<HashMap<int, int, HashInt> > 
        hash_all("HashMapAllRandom", 100000, 10000000, &t);

    if (t.test_all()) puts("All tests have finished without errors.");
    else return 1;
    return 0;
}

