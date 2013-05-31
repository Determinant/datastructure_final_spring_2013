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

#ifndef TESTCASES_H
#define TESTCASES_H

#include "unittest.h"
#include "HashMap.h"
#include "TreeMap.h"
#include "ArrayList.h"
#include "LinkedList.h"

#define LIST_TEMPLATE_HEADER template<template <class> class List>
#define MAP_TEMPLATE_HEADER template<template <class> class Map>

using UnitTest::TestCase;
using UnitTest::TestFixture;
using UnitTest::TestException;

LIST_TEMPLATE_HEADER
class ListTest : public TestCase {/*{{{*/
    protected:
        List<int> *arr_ptr;
    public:
        ListTest(TestFixture *_fixture) : 
            TestCase(_fixture) {}

        void print_array_list() {

            for (int i = 0; i < arr_ptr -> size(); i++)
                printf("%d ", arr_ptr -> get(i));
            puts("");

            for (typename List<int>::Iterator it = arr_ptr -> iterator();
                    it.hasNext();)
                printf("%d ",  it.next());
            puts("");
        }

        void set_up() {
            arr_ptr = new List<int>();
        }

        void tear_down() {
            delete arr_ptr;
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestConsecutiveInsert: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestConsecutiveInsert(int _times, TestFixture *_fixture) : 
            ListTest<List>(_fixture), times(_times) {}
        void set_up() {
            puts("== Now preparing to test Consecutive Insertion...");
            ListTest<List>::set_up();
        }
        void tear_down() {
            puts("== Finishing the test...");
            ListTest<List>::tear_down();
        }
        void run_test() {
            for (int i = 0; i < times; i++)
                this -> arr_ptr -> add(i);
            this -> print_array_list();
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestModification: public ListTest<List> {/*{{{*/
    private:
        int bound;
    public:
        ListTestModification(int _bound, TestFixture *_fixture):
            ListTest<List>(_fixture), bound(_bound) {}
        void set_up() {
            puts("== Now preparing to test Modification...");
            ListTest<List>::set_up();
        }

        void tear_down() {
            puts("== Finishing the test Mofification...");
            ListTest<List>::tear_down();
        }

        void run_test() {
            for (int i = 0; i < bound; i++)
                this -> arr_ptr -> add(0);
            for (int i = 0; i < bound; i += 2)
                this -> arr_ptr -> set(i, -1);
            for (int i = 1; i < bound; i += 2)
                this -> arr_ptr -> set(i, 1);

            this -> print_array_list();
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestRepetitiveClear: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestRepetitiveClear(int _times, TestFixture *_fixture):
            ListTest<List>(_fixture), times(_times) {}
        void set_up() {
            puts("== Now preparing to test Repetitive Clear...");
            ListTest<List>::set_up();
        }

        void tear_down() {
            puts("== Finishing the test Repetitive Clear...");
            ListTest<List>::tear_down();
        }

        void run_test() {
            for (int t = 0; t < 100; t++)
            {
                for (int i = 0; i < 100; i++)
                    this -> arr_ptr -> add(0);
                this -> print_array_list();
                this -> arr_ptr -> clear();
                this -> print_array_list();
                if (!this -> arr_ptr -> isEmpty())
                    throw TestException("The cleared container should be empty");
            }
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestInsertAndRemove: public ListTest<List> {/*{{{*/
    private:
        int bound;
    public:
        ListTestInsertAndRemove(int _bound, TestFixture *_fixture):
            ListTest<List>(_fixture), bound(_bound) {}
        void set_up() {
            puts("== Now preparing to test Insert and Remove...");
            ListTest<List>::set_up();
        }

        void tear_down() {
            puts("== Finishing the test Insert and Remove...");
            ListTest<List>::tear_down();
        }

        void run_test() {
            for (int t = 0; t < bound; t += 2)
            {
                for (int i = 0; i < t; i++)
                    this -> arr_ptr -> add(i);
                for (int i = 0; i * 2 < t; i++)
                    this -> arr_ptr -> remove(i * 2);
                this -> print_array_list();
                this -> arr_ptr -> clear();

                for (int i = 0; i < t; i++)
                    this -> arr_ptr -> add(i);
                for (int i = 0; i * 2 + 1< t; i++)
                    this -> arr_ptr -> remove(i * 2 + 1);
                this -> print_array_list();
                this -> arr_ptr -> clear();
            }
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestIterator: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestIterator(TestFixture *_fixture):
            ListTest<List>(_fixture) {}
        void set_up() {
            puts("== Now preparing to test Iterator...");
            ListTest<List>::set_up();
        }

        void tear_down() {
            puts("== Finishing the test Iterator...");
            ListTest<List>::tear_down();
        }

        void run_test() {
            for (int i = 0; i < 100; i++)
                this -> arr_ptr -> add(i);
            typename List<int>::Iterator it = this -> arr_ptr -> iterator();
            bool flag;

            try
            {
                flag = false;
                it.remove();
            }
            catch (ElementNotExist) 
            {
                flag = true;
            }
            if (!flag)
                throw TestException("The iterator is now pointer to the initial position"
                        ", nothing can be removed.");
            try
            {
                flag = false;
                it.next();
                it.remove();
                it.remove();
            }
            catch (ElementNotExist)
            {
                flag = true;
            }
            if (!flag) 
                throw TestException("The iterator should be temporary " 
                        "disabled after element deletion.");

            try
            {
                it.next();
                it.remove();
            }
            catch (ElementNotExist)
            {
                throw TestException("The iterator should be activated again "
                        "after the calling of next()");
            }
        }
};/*}}}*/

LIST_TEMPLATE_HEADER
class ListTestRandomOperation: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestRandomOperation(int _times, TestFixture *_fixture):
            ListTest<List>(_fixture), times(_times) {}
        void set_up() {
            puts("== Now preparing to test Random Operation...");
            ListTest<List>::set_up();
        }

        void tear_down() {
            puts("== Finishing the test Random Operation...");
            ListTest<List>::tear_down();
        }

        void run_test() {
            vector<int> std;
            int add_cnt = 0, rm_cnt = 0, set_cnt = 0, get_cnt = 0;
            for (int i = 0; i < 5; i++)
            {
                int size = 0;
                for (int i = 0; i < times; i++)
                {
                    int opt = rand() % 10;
                    if (!size || opt > 5)
                    {
                        int idx = rand() % (size + 1);
                        int num = rand();
                        this -> arr_ptr -> add(idx, num); 
                        std.insert(std.begin() + idx, num);
                        size++;
                        add_cnt++;
                    }
                    else if (size && opt == 5)
                    {
                        int idx = rand() % size;
                        this -> arr_ptr -> removeIndex(idx);
                        std.erase(std.begin() + idx);
                        size--;
                        rm_cnt++;
                    }
                    else if (size && opt <= 1)
                    {
                        int idx = rand() % size;
                        int num = rand();
                        this -> arr_ptr -> set(idx, num);
                        std[idx] = num;
                        set_cnt++;
                    }
                    else
                    {
                        int idx = rand() % size;
                        int num0 = this -> arr_ptr -> get(idx);
                        int num1 = std[idx];
                        if (num0 != num1) 
                            throw TestException("the answer from the list "
                                    "differs from the standard");
                        get_cnt++;
                    }
                }
                printf("Add: %d\nRemove:%d\nSet:%d\nGet:%d\n", add_cnt, rm_cnt, set_cnt, get_cnt);
                puts("All cleared.");
                std.clear();
                this -> arr_ptr -> clear();
            }
        }
};/*}}}*/

#endif
