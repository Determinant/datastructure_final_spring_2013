#include "unittest.h"
#include "HashMap.h"
#include "TreeMap.h"
#include "ArrayList.h"
#include "LinkedList.h"

using UnitTest::TestCase;
using UnitTest::TestFixture;
using UnitTest::TestException;

template<template <class> class List>
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

template<template <class> class List>
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

template<template <class> class List>
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

template<template <class> class List>
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

template<template <class> class List>
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

template<template <class> class List>
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
