/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#include <cstring>

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class Tp>
class ArrayList {
    private:
        /**
         * @var arr_ptr The pointer for manipulating the actual storage.
         * @var capacity The acutal memory that storage has occupied (in elements).
         * @var size The logical size of the desired array.
         * @var tp_size Pre-calced size of a element.
         */

        Tp *arr_ptr;
        int capacity, length, tp_size;

        void _realloc_space() {
            /*
             * @brief Double the space if it's necessary.
             * @warning It's assumed that the increasement of size is not large than 1
             */

            if (length > capacity)
            {
                if (capacity == 0) 
                {
                    capacity = 1;
                    arr_ptr = new Tp[1];
                }
                else
                {
                    capacity <<= 1;                         // double the capacity
                    Tp *tmp_ptr = new Tp[capacity];         // allocate a temporary space
                    memmove(tmp_ptr, arr_ptr, sizeof(Tp) * length);  // do copy
                    delete[] arr_ptr;                       // release the original space
                    arr_ptr = tmp_ptr;
                }
            }
        }

        void _check_index_range(int index) const {
            if (!(0 <= index && index < length))
                throw IndexOutOfBound(); // access violation
        }

    public:

        class Iterator;
        /**
         * TODO Constructs an empty array list.
         */
        ArrayList() { 
            arr_ptr = NULL;
            capacity = 0;
            length = 0;
            tp_size = sizeof(Tp);
        }

        /**
         * TODO Destructor
         */
        ~ArrayList() {
            delete[] arr_ptr;
        }

        /**
         * TODO Assignment operator
         */
        ArrayList& operator=(const ArrayList& other) { 
            capacity = other.capacity;
            length = other.length;
            if (arr_ptr != NULL) delete[] arr_ptr;
            arr_ptr = new Tp[capacity];
            memmove(arr_ptr, other.arr_ptr, sizeof(Tp) * length);
        }

        /**
         * TODO Copy-constructor
         */
        ArrayList(const ArrayList& other) {
            capacity = other.capacity;
            length = other.length;
            arr_ptr = new Tp[capacity];
            memmove(arr_ptr, other.arr_ptr, sizeof(Tp) * length);
        }


        /**
         * TODO Appends the specified element to the end of this list.
         * Always returns true.
         */
        bool add(const Tp& new_element) {
            length++;
            _realloc_space();
            arr_ptr[length - 1] = new_element;
            return true;
        }

        /**
         * TODO Inserts the specified element to the specified position in this list.
         * The range of index parameter is [0, size], where index=0 means inserting to the head,
         * and index=size means appending to the end.
         * @throw IndexOutOfBound
         */
        void add(int before_idx, const Tp& element) {

            length++;
            _check_index_range(before_idx);
            _realloc_space();
            for (int i = length - 1; i > before_idx; i--)
                arr_ptr[i] = arr_ptr[i - 1];
            arr_ptr[before_idx] = element;
        }

        /**
         * TODO Removes all of the elements from this list.
         */
        void clear() { length = 0; }

        /**
         * TODO Returns true if this list contains the specified element.
         */
        bool contains(const Tp& element) const {
            for (int i = 0; i < length; i++)
                if (arr_ptr[i] == element) return true;
            return false;
        }

        /**
         * TODO Returns a const reference to the element at the specified position in this list.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        const Tp& get(int index) const {
            _check_index_range(index);
            return arr_ptr[index];
        }

        /**
         * TODO Returns true if this list contains no elements.
         */
        bool isEmpty() const { return length == 0; }

        /**
         * TODO Removes the element at the specified position in this list.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        void removeIndex(int index) {
            _check_index_range(index);
            length--;
            for (int i = index; i < length; i++)
                arr_ptr[i] = arr_ptr[i + 1];
        }

        /**
         * TODO Removes the first occurrence of the specified element from this list, if it is present.
         * Returns true if it was present in the list, otherwise false.
         */
        bool remove(const Tp &element) {
            for (int i = 0; i < length; i++)
                if (arr_ptr[i] == element)
                {
                    removeIndex(i);
                    return true;
                }
            return false;
        }

        /**
         * TODO Replaces the element at the specified position in this list with the specified element.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        void set(int index, const Tp &element) {
            _check_index_range(index);
            arr_ptr[index] = element;
        }

        /**
         * TODO Returns the number of elements in this list.
         */
        int size() const { return length; }

        /**
         * TODO Returns an iterator over the elements in this list.
         */
        Iterator iterator() { return Iterator(this); }
};

template<class Tp>
class ArrayList<Tp>::Iterator {

    private:
        int cursor;
        ArrayList *container;
        bool dead;

    public:

        Iterator(): dead(true) {}
        Iterator(ArrayList *con) :  cursor(0), container(con), dead(false){}
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            if (dead) return false;
            return cursor < container -> length;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Tp &next() {
            if (!hasNext()) dead = true;
            if (dead) throw ElementNotExist();
            return container -> arr_ptr[cursor++];
        }

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() {
            if (dead) throw ElementNotExist();
            if (--cursor < 0)
            {
                dead = true;
                throw ElementNotExist();
            }
            container -> removeIndex(cursor);
        }
};

#endif
