/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList
{
public:
    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {}

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() {}
    };

    /**
     * TODO Constructs an empty array list.
     */
    ArrayList() { }

    /**
     * TODO Destructor
     */
    ~ArrayList() { }

    /**
     * TODO Assignment operator
     */
    ArrayList& operator=(const ArrayList& x) { }

    /**
     * TODO Copy-constructor
     */
    ArrayList(const ArrayList& x) { }

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {}

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) {}

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() {}

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const {}

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {}

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const {}

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index) {}

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) {}

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) {}

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const {}

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator() {}
};

#endif
