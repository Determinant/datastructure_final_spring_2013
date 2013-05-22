/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList
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
     * TODO Constructs an empty linked list
     */
    LinkedList() {}

    /**
     * TODO Copy constructor
     */
    LinkedList(const LinkedList<T> &c) {}

    /**
     * TODO Assignment operator
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {}

    /**
     * TODO Desturctor
     */
    ~LinkedList() {}

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {}

    /**
     * TODO Inserts the specified element to the beginning of this list.
     */
    void addFirst(const T& elem) {}

    /**
     * TODO Insert the specified element to the end of this list.
     * Equivalent to add.
     */
    void addLast(const T &elem) {}

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
     * TODO Returns a const reference to the first element.
     * @throw ElementNotExist
     */
    const T& getFirst() const {}

    /**
     * TODO Returns a const reference to the last element.
     * @throw ElementNotExist
     */
    const T& getLast() const {}

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
     * TODO Removes the first element from this list.
     * @throw ElementNotExist
     */
    void removeFirst() {}

    /**
     * TODO Removes the last element from this list.
     * @throw ElementNotExist
     */
    void removeLast() {}

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
