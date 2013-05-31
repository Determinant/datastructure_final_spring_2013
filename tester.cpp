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

int main() {

    TestFixture t;
    ListTestConsecutiveInsert<ArrayList> arr_altci(1000, &t);
    ListTestModification<ArrayList> arr_altm(100, &t);
    ListTestRepetitiveClear<ArrayList> arr_altpc(100, &t);
    ListTestInsertAndRemove<ArrayList> arr_altir(100, &t);
    ListTestIterator<ArrayList> arr_alti(&t);
    ListTestRandomOperation<ArrayList> arr_ro(100000, &t);

    ListTestConsecutiveInsert<LinkedList> linked_altci(1000, &t);
    ListTestModification<LinkedList> linked_altm(100, &t);
    ListTestRepetitiveClear<LinkedList> linked_altpc(100, &t);
    ListTestInsertAndRemove<LinkedList> linked_altir(100, &t);
    ListTestIterator<LinkedList> linked_alti(&t); 
    ListTestRandomOperation<LinkedList> linked_ro(100000, &t);

    if (t.test_all()) puts("All tests have finished without errors.");
    else return 1;
    return 0;
}

