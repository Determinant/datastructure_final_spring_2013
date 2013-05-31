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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this
 * list.
 */

template <class Tp>
class LinkedList {
    private:
        struct Node;
        /**
         * @var head Sentinel node to mark the beginning and end of the list.
         * @var length The total number of elements in the list.
         */

        Node *head;
        int length;

        void _clear_nodes() {
            /*
             * @brief Free all allocated nodes in storage.
             * Note that head is reset properly and length is cleared.
             */
            for (Node *p = head -> next, *np; p != head; p = np)
            {
                np = p -> next;
                delete p;
            }
            head -> next = head -> prev = head; // self-loop
            length = 0;
        }

        void _check_index_range(int index) const {
            /*
             * @brief Check and throw IndexOutOfBound when index is out of
             * range.
             */
            if (!(0 <= index && index < length))
                throw IndexOutOfBound(); // access violation
        }

        void _check_empty() const {
            /*
             * @brief Check and throw ElementNotExist when the container is
             * empty.
             */
            if (isEmpty()) throw ElementNotExist();
        }

        void _erase_node(Node *p) {
            /*
             * @brief Erase a node in the list and free its memory.
             */
            p -> next -> prev = p -> prev;
            p -> prev -> next = p -> next;
            delete p;
            length--;
        }

    public:

        class Iterator;

        LinkedList() {
            /**
             * @brief Constructs an empty linked list
             */
            head = new Node();
            head -> prev = head -> next = head;
            length = 0;
        }

        LinkedList(const LinkedList<Tp> &other) {
            /**
             * @brief Copy constructor
             */
            head = new Node();
            head -> prev = head -> next = head;
            length = 0;

            Node *p, *op;
            for (p = head, op = other.head -> next; 
                    op != other.head; 
                    p = p -> next, op = op -> next)
                p -> next = new Node(p, NULL, op -> data);
            (p -> next = head) -> prev = p;
            length = other.length;
        }

        LinkedList<Tp>& operator=(const LinkedList<Tp> &other) {
            /**
             * @brief Assignment operator
             */

            if (this != &other)
            {
                _clear_nodes();
                Node *p, *op;
                for (p = head, op = other.head -> next; 
                        op != other.head; 
                        p = p -> next, op = op -> next)
                    p -> next = new Node(p, NULL, op -> data);
                (p -> next = head) -> prev = p;
                length = other.length;
            }
            return *this;
        }

        ~LinkedList() {
            /**
             * @brief Desturctor
             */

            _clear_nodes();
            delete head;
        }

        bool add(const Tp& element) {
            /**
             * @brief Appends the specified element to the end of this list.
             * @warning Always returns true.
             */

            addLast(element);
            return true;
        }

        void addFirst(const Tp& element) {
            /**
             * @brief Inserts the specified element to the beginning of this
             * list.
             */
            Node *tmp_ptr = new Node(head, head -> next, element);
            head -> next = tmp_ptr;
            tmp_ptr -> next -> prev = tmp_ptr;
            length++;
        }

        void addLast(const Tp &element) {
            /**
             * @brief Insert the specified element to the end of this list.
             * @warning Equivalent to add.
             */

            Node *tmp_ptr = new Node(head -> prev, head, element);
            head -> prev = tmp_ptr;
            tmp_ptr -> prev -> next = tmp_ptr;
            length++;
        }

        void add(int index, const Tp& element) {
            /**
             * @brief Inserts the specified element to the specified position in
             * this list.
             * The range of index parameter is [0, size], where index=0 means
             * inserting to the head, and index=size means appending to the
             * end.
             * @throw IndexOutOfBound
             */

            length++;
            _check_index_range(index);
            Node *p = head;
            for (int i = 0; i < index; i++) p = p -> next;
            Node *tmp_ptr = new Node(p, p -> next, element);
            p -> next = tmp_ptr;
            tmp_ptr -> next -> prev = tmp_ptr;
        }

        // @brief Removes all of the elements from this list.
        void clear() { _clear_nodes(); }

        bool contains(const Tp& element) const {
            /**
             * @brief Returns true if this list contains the specified element.
             */

            for (Node *p = head -> next; p != head; p = p -> next)
                if (p -> data == element) return true;
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
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            return p -> data;
        }
        const Tp& getFirst() const {

            /**
             * @brief const reference to the first element.
             * @throw ElementNotExist
             */

            _check_empty();
            return head -> next -> data;
        }

        const Tp& getLast() const {
            /**
             * @brief Returns a const reference to the last element.
             * @throw ElementNotExist
             */

            _check_empty();
            return head -> prev -> data;
        }

        // @brief Returns true if this list contains no elements.
        bool isEmpty() const { return head -> prev == head; }

        void removeIndex(int index) {
            /**
             * @brief Removes the element at the specified position in this
             * list.
             * The index is zero-based, with range [0, size).
             * @throw IndexOutOfBound
             */

            _check_index_range(index);
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            _erase_node(p);
        }

        bool remove(const Tp &element) {

            /**
             * @brief Removes the first occurrence of the specified element from
             * this list, if it is present.  Returns true if it was present in
             * the list, otherwise false.
             */

            for (Node *p = head -> next; p != head; p = p -> next)
                if (p -> data == element)
                {
                    _erase_node(p);
                    return true;
                }
            return false;
        }

        void removeFirst() {
            /**
             * @brief Removes the first element from this list.
             * @throw ElementNotExist
             */

            _check_empty();
            _erase_node(head -> next);
        }

        void removeLast() {
            /**
             * @brief Removes the last element from this list.
             * @throw ElementNotExist
             */

            _check_empty();
            _erase_node(head -> prev);
        }

        void set(int index, const Tp &element) {
            /**
             * @brief Replaces the element at the specified position in this
             * list with the specified element.
             * The index is zero-based, with range [0, size).
             * @throw IndexOutOfBound
             */

            _check_index_range(index);
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            p -> data = element;
        }

        // @brief Returns the number of elements in this list.
        int size() const { return length; }

        // @brief Returns an iterator over the elements in this list.
        Iterator iterator() { return Iterator(this); }
};

template <class Tp> 
struct LinkedList<Tp>::Node {
    Node *prev, *next; 
    Tp data;
    Node() {}
    Node(Node *_prev, Node *_next, const Tp &_data) 
        : prev(_prev), next(_next), data(_data) {}
};

template <class Tp>
class LinkedList<Tp>::Iterator {
    private:
        /**
         * @var cursor Indicate the current index to which the iterator is
         * pointing
         * @var container Reflect pointer to the container to which it applies
         * @var dead True if it has been removed but next has not been called.
         */
        Node *cursor;
        LinkedList *container;
        bool dead;
    public:
        Iterator() {}
        Iterator(LinkedList *con) : 
            cursor(con -> head), container(con), dead(false) {}

        // @brief Returns true if the iteration has more elements.
        bool hasNext() { return cursor -> next != container -> head; }

        const Tp &next() { 
            /**
             * @brief Returns the next element in the iteration.
             * @throw ElementNotExist exception when hasNext() == false
             */

            if (!hasNext()) throw ElementNotExist();
            if (dead) dead = false; // revive
            return (cursor = cursor -> next) -> data;
        }

        void remove() {
            /**
             * @brief Removes from the underlying collection the last element
             * returned by the iterator
             * The behavior of an iterator is unspecified if the underlying
             * collection is modified while the iteration is in progress in
             * any way other than by calling this method.
             * @throw ElementNotExist
             */

            if (cursor == container -> head || dead) 
                throw ElementNotExist();
            dead = true;
            Node *pcursor = cursor -> prev;
            container -> _erase_node(cursor);
            cursor = pcursor;
        }
};

#endif
