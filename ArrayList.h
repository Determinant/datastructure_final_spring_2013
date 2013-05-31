/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#include <cstring>

/**
 * The ArrayList is just like vector in C++.  You should know that "capacity"
 * here doesn't mean how many elements are now in this list, where it means the
 * length of the array of your internal implemention.
 *
 * The iterator iterates in the order of the elements being loaded into this
 * list.
 */

template <class Tp>
class ArrayList {
    private:
        /**
         * @var arr_ptr The pointer for manipulating the actual storage.
         * @var capacity The acutal memory that storage has occupied (in
         * elements).
         * @var size The logical size of the desired array.
         * @var tp_size Pre-calced size of a element.
         */

        Tp *arr_ptr;
        int capacity, length, tp_size;

        void _realloc_space() {
            /**
             * @brief Double the space if necessary.
             * @warning It's assumed that the increasement of size is not larger
             * than one
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
                    capacity <<= 1; 
                    Tp *tmp_ptr = new Tp[capacity]; 
                    // double the capacity
                    memmove(tmp_ptr, arr_ptr, sizeof(Tp) * length); 
                    delete[] arr_ptr; 
                    // move and free the original space
                    arr_ptr = tmp_ptr;
                }
            }
        }

        void _check_index_range(int index) const {
            /**
             * @brief Check and throw IndexOutOfBound when index is out of
             * range.
             */
            if (!(0 <= index && index < length))
                throw IndexOutOfBound(); // access violation
        }

    public:

        class Iterator;

        ArrayList() { 
            /**
             * @brief Constructs an empty array list.
             */
            arr_ptr = NULL;
            capacity = 0;
            length = 0;
            tp_size = sizeof(Tp);
        }

        ~ArrayList() {
            /**
             * @brief Destructor. Try to release all the memory allocated via
             * arr_ptr;
             */
            delete[] arr_ptr;
        }

        ArrayList& operator=(const ArrayList& other) { 
            /**
             * @brief Assignment operator
             */
            if (this != &other)
            {
                capacity = other.capacity;
                length = other.length;
                if (arr_ptr != NULL) delete[] arr_ptr;
                arr_ptr = new Tp[capacity];
                memmove(arr_ptr, other.arr_ptr, sizeof(Tp) * length);
            }
            return *this;
        }

        ArrayList(const ArrayList& other) {
            /**
             * @brief Copy-constructor. Copy the whole storage memory to the
             * new-born instance.
             */
            capacity = other.capacity;
            length = other.length;
            arr_ptr = new Tp[capacity];
            memmove(arr_ptr, other.arr_ptr, sizeof(Tp) * length);
        }


        bool add(const Tp& new_element) {
            /**
             * @brief Appends the specified element to the end of this list.
             * @warning Always returns true.
             */

            length++;
            _realloc_space(); // try to double space
            arr_ptr[length - 1] = new_element;
            return true;
        }

        void add(int before_idx, const Tp& element) {

            /**
             * @brief Inserts the specified element to the specified position in
             * this list.
             * The range of index parameter is [0, size], where index=0 means
             * inserting to the head, and index=size means appending to the end.
             * @throw IndexOutOfBound
             */

            length++;
            _check_index_range(before_idx);
            _realloc_space();
            for (int i = length - 1; i > before_idx; i--)
                arr_ptr[i] = arr_ptr[i - 1];
            arr_ptr[before_idx] = element;
        }

        // @brief Removes all of the elements from this list.
        void clear() { length = 0; }

        bool contains(const Tp& element) const {
            /**
             * @brief Returns true if this list contains the specified element.
             */

            for (int i = 0; i < length; i++)
                if (arr_ptr[i] == element) return true;
            return false;
        }

        const Tp& get(int index) const {
            /**
             * @brief Returns a const reference to the element at the specified
             * position in this list.
             * The index is zero-based, with range [0, size).
             * @throw IndexOutOfBound
             */

            _check_index_range(index);
            return arr_ptr[index];
        }

        // @brief Returns true if this list contains no elements.
        bool isEmpty() const { return length == 0; }

        void removeIndex(int index) {
            /**
             * @brief Removes the element at the specified position in this
             * list.
             * The index is zero-based, with range [0, size).
             * @throw IndexOutOfBound
             */

            _check_index_range(index);
            length--;
            for (int i = index; i < length; i++)
                arr_ptr[i] = arr_ptr[i + 1];
        }

        bool remove(const Tp &element) {
            /**
             * @brief Removes the first occurrence of the specified element from
             * this list, if it is present.
             * Returns true if it was present in the list, otherwise false.
             */

            for (int i = 0; i < length; i++)
                if (arr_ptr[i] == element)
                {
                    removeIndex(i);
                    return true;
                }
            return false;
        }

        void set(int index, const Tp &element) {
            /**
             * @brief Replaces the element at the specified position in this
             * list with the specified element.
             * The index is zero-based, with range [0, size).
             * @throw IndexOutOfBound
             */

            _check_index_range(index);
            arr_ptr[index] = element;
        }

        // @brief Returns the number of elements in this list.
        int size() const { return length; }

        // @brief Returns an iterator over the elements in this list.
        Iterator iterator() { return Iterator(this); }
};

template<class Tp>
class ArrayList<Tp>::Iterator {

    private:

        /**
         * @var cursor Indicate the current index to which the iterator is
         * pointing
         * @var container Reflect pointer to the container to which it applies
         * @var dead True if it has been removed but next has not been called.
         */
        int cursor;
        ArrayList *container;
        bool dead;

    public:

        Iterator() {}
        Iterator(ArrayList *con) : 
            cursor(0), container(con), dead(false) {}

        // @brief Returns true if the iteration has more elements.
        bool hasNext() { return cursor < container -> length; }

        const Tp &next() {
            /**
             * @brief Returns the next element in the iteration.
             * @throw ElementNotExist exception when hasNext() == false
             */

            if (!hasNext()) throw ElementNotExist();
            if (dead) dead = false; // revive
            return container -> arr_ptr[cursor++];
        }

        void remove() {
            /**
             * @brief Removes from the underlying collection the last element
             * returned by the iterator
             * The behavior of an iterator is unspecified if the underlying
             * collection is modified while the iteration is in progress in any
             * way other than by calling this method.
             * @throw ElementNotExist
             */

            if (cursor - 1 < 0 || dead) throw ElementNotExist(); 
            // not pointing to any valid position
            container -> removeIndex(--cursor);
        }
};

#endif
