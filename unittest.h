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
    printf("+ allocate mem size %d at %llx\n", (int)size, (ll)p);
    if (NULL == p)
        puts("Can not allocate memory");
    return p;
}

void operator delete(void * p) throw() {

    total_alloc_cnt--;
    free(p);
    printf("- %llx\n", (ll)p);
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

        TestFixture *fixture;
        int base_alloc_cnt;

        public:
        TestCase(TestFixture *_fixture): fixture(_fixture) {
            fixture -> add_case(this);
            base_alloc_cnt = total_alloc_cnt;
        }

        ~TestCase() {
            printf("Net Alloc Cnt: %d\n", total_alloc_cnt - base_alloc_cnt);
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
