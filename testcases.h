/**
 * Copyright (C) 2013 
 *
 * Ted Yin <ted.sybil@gmail.com>
 * Liao Chao <zeonsgtr@gmail.com>
 *
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

#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <algorithm>

using UnitTest::TestCase;
using UnitTest::TestFixture;
using UnitTest::TestException;

using std::random_shuffle;
using std::make_pair;
using std::vector;
using std::pair;
using std::sort;
using std::set;

template <class List>
class ListTest : public TestCase {/*{{{*/
    protected:
        List *arr_ptr;
    public:
        ListTest(TestFixture *_fixture) : 
            TestCase("ListTest", _fixture) {}
        ListTest(string case_name, TestFixture *_fixture) : 
            TestCase(case_name, _fixture) {}

        void print_array_list() {

            for (int i = 0; i < arr_ptr -> size(); i++)
                printf("%d ", arr_ptr -> get(i));
            puts("");

            for (typename List::Iterator it = arr_ptr -> iterator();
                    it.hasNext();)
                printf("%d ",  it.next());
            puts("");
        }

        void set_up() {
            this -> start_memory_watching();
            arr_ptr = new List();
        }

        void tear_down() {
            delete arr_ptr;
            this -> stop_memory_watching();
        }
};/*}}}*/

template <class List>
class ListTestConsecutiveInsert: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestConsecutiveInsert(int _times, TestFixture *_fixture) : 
            ListTest<List>("ListTestConsecutiveInsert", _fixture), times(_times) {}

        ListTestConsecutiveInsert(string case_name, int _times, TestFixture *_fixture) : 
            ListTest<List>(case_name, _fixture), times(_times) {}

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

template <class List>
class ListTestModification: public ListTest<List> {/*{{{*/
    private:
        int bound;
    public:
        ListTestModification(int _bound, TestFixture *_fixture):
            ListTest<List>("ListTestModification", _fixture), bound(_bound) {}
        ListTestModification(string case_name, int _bound, TestFixture *_fixture):
            ListTest<List>(case_name, _fixture), bound(_bound) {}

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

template <class List>
class ListTestRepetitiveClear: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestRepetitiveClear(int _times, TestFixture *_fixture):
            ListTest<List>("ListTestRepetitiveClear", _fixture), times(_times) {}
        ListTestRepetitiveClear(string case_name, int _times, TestFixture *_fixture):
            ListTest<List>(case_name, _fixture), times(_times) {}

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

template <class List>
class ListTestInsertAndRemove: public ListTest<List> {/*{{{*/
    private:
        int bound;
    public:
        ListTestInsertAndRemove(int _bound, TestFixture *_fixture):
            ListTest<List>("ListTestInsertAndRemove", _fixture), bound(_bound) {}
        ListTestInsertAndRemove(string case_name, int _bound, TestFixture *_fixture):
            ListTest<List>(case_name, _fixture), bound(_bound) {}

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

template <class List>
class ListTestIterator: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestIterator(TestFixture *_fixture):
            ListTest<List>("ListTestIterator", _fixture) {}
        ListTestIterator(string case_name, TestFixture *_fixture):
            ListTest<List>(case_name, _fixture) {}

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
            typename List::Iterator it = this -> arr_ptr -> iterator();
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

template <class List>
class ListTestRandomOperation: public ListTest<List> {/*{{{*/
    private:
        int times;
    public:
        ListTestRandomOperation(int _times, TestFixture *_fixture):
            ListTest<List>("ListTestRandomOperation", _fixture), times(_times) {}
        ListTestRandomOperation(string case_name, int _times, TestFixture *_fixture):
            ListTest<List>(case_name, _fixture), times(_times) {}

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
                srand(time(0));
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

/*{{{ Map Tester thanks to Liao Chao */
template <class Map>
class MapTest: public TestCase { /*{{{*/
	protected:
		Map *map_ptr;

	public:
		MapTest(TestFixture *_fixture): 
            TestCase("MapTest", _fixture) {}
		MapTest(string case_name, TestFixture *_fixture): 
            TestCase(case_name, _fixture) {}

		void print_map_elems() {
			for (typename Map::Iterator it = map_ptr->iterator(); it.hasNext(); ) {
				typename Map::Entry tmp = it.next(); 
				printf("(%d, %d) ", tmp.getKey(), tmp.getValue());
			}
			puts("");
		}

		void set_up() {
            this -> start_memory_watching();
			map_ptr = new Map();
		}

		void tear_down() {
			delete map_ptr;
            this -> stop_memory_watching();
		}
};/*}}}*/

template <class Map>
class MapTestAllRandomly: public MapTest <Map> {/*{{{*/
	private:
		int times, upper;

		int _rand() {
			return (rand() ^ rand()) % upper;
		}

	public:
		MapTestAllRandomly(int _times, int _upper, TestFixture *_fixture):
			MapTest <Map>("MapTestAllRandomly", _fixture), times(_times), upper(_upper) {}
		MapTestAllRandomly(string case_name, int _times, int _upper, TestFixture *_fixture):
			MapTest <Map>(case_name, _fixture), times(_times), upper(_upper) {}

		void set_up() {
			if (times == 0) {
				throw TestException("Ooooops, wrong argument @times");
			}
			if (upper == 0) {
				throw TestException("Ooooops, wrong argument @upper");
			}
			if (times > upper) {
				throw TestException("Ooooops, wrong argument @times @upper, @times");
			}
			puts("== Now Preparing to test all randomly...");
			MapTest <Map>::set_up();
		}

		void tear_down() {
			puts("== Finishing the test...");
			MapTest <Map>::tear_down();
		}

		void run_test() {
			srand(time(0));
			vector <pair <int, int> > events;
			set <int> all_keys;
			for (int i = 0; i < times; i++) {
				while (true) {
					int a = _rand(), b = _rand();
					if (all_keys.count(a)) {
						continue;
					}
					all_keys.insert(a);
					events.push_back(make_pair(a, b));
					this->map_ptr->put(a, b);
					break;
				}
			}
			/*
			puts("\nall elements:");
			this->print_map_elems();
			puts("");
			*/

			int counter = 0;
			/**
			 * test the Iterator & Insertion
			 * Ooooops, I fount out that this checker is not always true for HashMap.
			 */
			/*
			puts("checking the Iterator & Insertion:");
			sort(events.begin(), events.end());
			for (typename Map::Iterator it = this->map_ptr
					->iterator(); it.hasNext(); ) {
				typename Map::Entry tmp = it.next();
				if (tmp.getKey() != events[counter].first || tmp.getValue() != events[counter].second) {
					throw TestException("Ooooops, the Iterator of the Map "\
							"gives wrong logical tree structure!!!");
				}
				counter++;
			}
			puts("OK\n");
			*/

			/**
			 * test the clear() function & isEmpty() function
			 */
			puts("checking clear() function & isEmpty() function:");
			this->map_ptr->clear();
			if (!this->map_ptr->isEmpty()) {
				throw TestException("Ooooops, the clear() fucntion gose wrong!!!");
			}
			for (int i = 0; i < (int)events.size(); i++) {
				this->map_ptr->put(events[i].first, events[i].second);
			}
			/* Ooooops, I fount out that this checker is not always true for HashMap. 
			counter = 0;
			for (typename Map::Iterator it = this->map_ptr
					->iterator(); it.hasNext(); ) {
				typename Map::Entry tmp = it.next();
				if (tmp.getKey() != events[counter].first || tmp.getValue() != events[counter].second) {
					throw TestException("Ooooops, the Iterator of the Map "\
							"gives wrong logical tree structure afther clear() operation!!!");
				}
				counter++;
			}
			*/
			puts("OK\n");

			/**
			 * test Hu Gao.....
			 */
			puts("jiu shi yao hu gao:");
			events.clear();
			for (int i = 0; i < (int)events.size(); i++) {
				while (true) {
					int r = _rand();
					set <int>::iterator e = all_keys.lower_bound(r);
					if (e == all_keys.end()) {
						continue;
					}
					r = *e;
					all_keys.erase(r);
					this->map_ptr->remove(r);
					if (this->map_ptr->containsKey(r)) {
						throw TestException("Ooooops, the containsKey() function of the Map "\
								"goes wrong!!!");
					}
					break;
				}
				while (true) {
					int r = _rand();
					if (all_keys.find(r) != all_keys.end()) {
						continue;
					}
					all_keys.insert(r);
					int t = _rand();
					this->map_ptr->put(r, t);
					if (this->map_ptr->get(r) != t) {
						throw TestException("Ooooops, the get() function of the Map"\
								"goes wrong!!!");
					}
					break;
				}
			}
			for (typename Map::Iterator it = this->map_ptr->iterator();
					it.hasNext(); ) {
				typename Map::Entry tmp = it.next();
				events.push_back(make_pair(tmp.getKey(), tmp.getValue()));
			}
			puts("OK\n");

			/**
			 * test the containsKey() function
			 */
			puts("checking containKey() function:");
			random_shuffle(events.begin(), events.end());
			for (int i = 0; i < (int)events.size(); i++) {
				//printf("checkIndex=%d key=%d value=%d\n", i, events[i].first, events[i].second);
				if (this->map_ptr->containsKey(events[i].first) == false) {
					throw TestException("Ooooops, the containsKey() function of the Map "\
							"goes wrong!!!");
				}
				int r = _rand();
				//printf("randomly check value = %d %d %d\n", r, this->map_ptr->containsKey(events[i].first), all_keys.count(r));
				if (this->map_ptr->containsKey(r) != all_keys.count(r)) {
					throw TestException("Ooooops, the containsKey() function of the Map "\
							"goes wrong!!!");
				}
			}
			puts("OK\n");

			/**
			 * test the get() function & put() function
			 */
			puts("check get() function & put() fucntion:");
			random_shuffle(events.begin(), events.end());
			for (int i = 0; i < (int)events.size(); i++) {
				if (this->map_ptr->get(events[i].first) != events[i].second) {
					throw TestException("Ooooops, the get() function of the Map"\
							"goes wrong!!!");
				}
				events[i].second = _rand();
				this->map_ptr->put(events[i].first, events[i].second);
				if (this->map_ptr->get(events[i].first) != events[i].second) {
					throw TestException("Ooooops, the put() function didn't take place"\
							"the new value!!!");
				}
			}
			puts("OK\n");

			/**
			 * test the remove() function & size() function
			 */
			puts("checking remove() function & size() function:");
			random_shuffle(events.begin(), events.end());
			for (int i = 0; i < (int)events.size(); i++) {
				//printf("checkIndex=%d key=%d value=%d\n", i, events[i].first, events[i].second);
				this->map_ptr->remove(events[i].first);
				if (this->map_ptr->containsKey(events[i].first)) {
					throw TestException("Ooooops, the remove() function "\
							"goes wrong!!!");
				}
				if (this->map_ptr->size() != (int)events.size() - i - 1) {
					throw TestException("Ooooops, the size() function "\
							"goes wrong!!!");
				}
			}
			puts("OK\n");
		}
};/*}}}*/ /*}}}*/
#endif
