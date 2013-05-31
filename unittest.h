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

#ifndef UNITTEST_H
#define UNITTEST_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <vector>

using std::string;
using std::set;
using std::vector;

typedef long long ll;

int total_alloc_cnt = 0;

void * operator new(size_t size) throw (std::bad_alloc) {
    void *p = malloc(size);
    total_alloc_cnt++;
    //fprintf(stderr,"+ allocate mem size %d at %llx\n", (int)size, (ll)p);
    /*if (NULL == p)
        fprintf(stderr, "Can not allocate memory");
        */
    return p;
}

void operator delete(void * p) throw() {

    total_alloc_cnt--;
    free(p);
    //fprintf(stderr, "- %llx\n", (ll)p);
}

namespace UnitTest {


    class TestException {
        string err_msg;
        public:
        TestException(const string _err_msg) : err_msg(_err_msg) {}
        const char *str() {
            return err_msg.c_str();
        }
    };

    class TestCase;
    class TestFixture {
        vector<TestCase*> cases;
        public:
        void add_case(TestCase *);
        bool test_all();
    };

    class TestCase {

        string case_name;
        TestFixture *fixture;
        int base_alloc_cnt, end_alloc_cnt;

        public:
        TestCase(TestFixture *_fixture): fixture(_fixture) {
            fixture -> add_case(this);
        }

        TestCase(string _case_name, TestFixture *_fixture) : 
            case_name(_case_name), fixture(_fixture) {
            fixture -> add_case(this);
        }

        ~TestCase() {
            printf("%s\t %d\n", 
                    case_name.c_str(),
                    end_alloc_cnt - base_alloc_cnt);
        }

        void start_memory_watching() {
            base_alloc_cnt = total_alloc_cnt;
        }

        void stop_memory_watching() {
            end_alloc_cnt = total_alloc_cnt;
        }

        virtual void set_up() {}
        virtual void run_test() = 0;
        virtual void tear_down() {}
    };

    void TestFixture::add_case(TestCase *_case) {
        cases.push_back(_case);
    }

    bool TestFixture::test_all() {
        for (vector<TestCase*>::iterator it = cases.begin(); 
                it != cases.end(); it++)
        {
            TestCase *cur = *it;
            cur -> set_up();
            try
            {
                cur -> run_test();
                cur -> tear_down();
            }
            catch (TestException e)
            {
                printf("The test aborted because of " \
                        "the error occured: %s\n", e.str());
                cur -> tear_down(); // clean up first
                return false;
            }
        }
        return true;
    }
}

#endif
