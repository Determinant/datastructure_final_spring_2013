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
template <class Tp>
class LinkedList
{
    private:
        struct Node;
        Node *head;
        int length;

        void _clear() {
            for (Node *p = head -> next, *np; p != head; p = np)
            {
                np = p -> next;
                delete p;
            }
            head -> next = head -> prev = head; // self-loop
            length = 0;
        }

        void _check_index_range(int index) const {
            if (!(0 <= index && index < length))
                throw IndexOutOfBound(); // access violation
        }

        void _check_empty() const {
            if (isEmpty()) throw ElementNotExist();
        }

        void _erase_node(Node *p) {
            p -> next -> prev = p -> prev;
            p -> prev -> next = p -> next;
            delete p;
            length--;
        }

    public:
    
        class Iterator;
        /**
         * TODO Constructs an empty linked list
         */
        LinkedList() {
            head = new Node();
            head -> prev = head -> next = head;
            length = 0;
        }

        /**
         * TODO Copy constructor
         */
        LinkedList(const LinkedList<Tp> &other) {
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

        /**
         * TODO Assignment operator
         */
        LinkedList<Tp>& operator=(const LinkedList<Tp> &other) {
            _clear();
            Node *p, *op;
            for (p = head, op = other.head -> next; 
                    op != other.head; 
                    p = p -> next, op = op -> next)
                p -> next = new Node(p, NULL, op -> data);
            (p -> next = head) -> prev = p;
            length = other.length;
            return *this;
        }

        /**
         * TODO Desturctor
         */
        ~LinkedList() {
            _clear();
            delete head;
        }

        /**
         * TODO Appends the specified element to the end of this list.
         * Always returns true.
         */
        bool add(const Tp& element) {
            addLast(element);
            return true;
        }

        /**
         * TODO Inserts the specified element to the beginning of this list.
         */
        void addFirst(const Tp& element) {
            Node *tmp_ptr = new Node(head, head -> next, element);
            head -> next = tmp_ptr;
            tmp_ptr -> next -> prev = tmp_ptr;
            length++;
        }

        /**
         * TODO Insert the specified element to the end of this list.
         * Equivalent to add.
         */
        void addLast(const Tp &element) {
            Node *tmp_ptr = new Node(head -> prev, head, element);
            head -> prev = tmp_ptr;
            tmp_ptr -> prev -> next = tmp_ptr;
            length++;
        }

        /**
         * TODO Inserts the specified element to the specified position in this list.
         * The range of index parameter is [0, size], where index=0 means inserting to the head,
         * and index=size means appending to the end.
         * @throw IndexOutOfBound
         */
        void add(int index, const Tp& element) {
            _check_index_range(index);
            Node *p = head;
            for (int i = 0; i < index; i++) p = p -> next;
            Node *tmp_ptr = new Node(p, p -> next, element);
            p -> next = tmp_ptr;
            tmp_ptr -> next -> prev = tmp_ptr;
            length++;
        }

        /**
         * TODO Removes all of the elements from this list.
         */
        void clear() { _clear(); }

        /**
         * TODO Returns true if this list contains the specified element.
         */
        bool contains(const Tp& element) const {
            for (Node *p = head -> next; p != head; p = p -> next)
                if (p -> data == element) return true;
            return false;
        }

        /**
         * TODO Returns a const reference to the element at the specified position in this list.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        const Tp& get(int index) const {
            _check_index_range(index);
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            return p -> data;
        }

        /**
         * TODO Returns a const reference to the first element.
         * @throw ElementNotExist
         */
        const Tp& getFirst() const {
            _check_empty();
            return head -> next -> data;
        }

        /**
         * TODO Returns a const reference to the last element.
         * @throw ElementNotExist
         */
        const Tp& getLast() const {
            _check_empty();
            return head -> prev -> data;
        }

        /**
         * TODO Returns true if this list contains no elements.
         */
        bool isEmpty() const { return head -> prev == head; }

        /**
         * TODO Removes the element at the specified position in this list.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        void removeIndex(int index) {
            _check_index_range(index);
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            _erase_node(p);
        }

        /**
         * TODO Removes the first occurrence of the specified element from this list, if it is present.
         * Returns true if it was present in the list, otherwise false.
         */
        bool remove(const Tp &element) {
            for (Node *p = head -> next; p != head; p = p -> next)
                if (p -> data == element)
                {
                    _erase_node(p);
                    return true;
                }
            return false;
        }

        /**
         * TODO Removes the first element from this list.
         * @throw ElementNotExist
         */
        void removeFirst() {
            _check_empty();
            _erase_node(head.next);
        }

        /**
         * TODO Removes the last element from this list.
         * @throw ElementNotExist
         */
        void removeLast() {
            _check_empty();
            _erase_node(head.prev);
        }

        /**
         * TODO Replaces the element at the specified position in this list with the specified element.
         * The index is zero-based, with range [0, size).
         * @throw IndexOutOfBound
         */
        void set(int index, const Tp &element) {
            _check_index_range(index);
            Node *p = head -> next;
            for (int i = 0; i < index; i++) p = p -> next;
            p -> data = element;
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

template <class Tp> 
struct LinkedList<Tp>::Node {
    Node *prev, *next; 
    Tp data;
    Node() {}
    Node(Node *_prev, Node *_next, const Tp &_data) : prev(_prev), next(_next), data(_data) {}
};

template <class Tp>
class LinkedList<Tp>::Iterator {
    private:
        Node *cursor;
        LinkedList *container;

    public:
        Iterator(LinkedList *con) : cursor(con -> head), container(con) {}
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() { return cursor -> next != container -> head; }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Tp &next() { 
            if (!hasNext()) throw ElementNotExist();
            return (cursor = cursor -> next) -> data;
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
            if (cursor == container -> head) throw ElementNotExist();
            Node *pcursor = cursor -> prev;
            container -> _erase_node(cursor);
            cursor = pcursor;
        }
};

#endif
