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

#ifndef HASHMAP_H
#define HASHMAP_H

#include "ElementNotExist.h"
#include <cstring>

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of
 * the elements.
 *
 * Template argument Hash are used to specify the hash function.  Hash should
 * be a class with a static function named ``hashCode'', which takes a
 * parameter of type Key and returns a value of type int.  For example, the
 * following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two
 * keys are equal (which means key1 == key2), then the hash code of them should
 * be the same. However, it is not generally required that the hash function
 * should work in the other direction: if the hash code of two keys are equal,
 * the two keys could be different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash
 * function.  This is to say that, even the given hash function always returns
 * the same hash code for all keys (thus causing a serious collision), methods
 * of HashMap should still function correctly, though the performance will be
 * poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be
 * guaranteed that each (key, value) pair be iterated exactly once.
 */

template <class Key, class Val, class Hash>
class HashMap
{
    private:
        struct Node;
        /**
         * @var HASH_TABLE_SIZE The size of bucket which is expected to be a
         * prime.
         * @var head The bucket, an array of pointers to Node instance.
         * @var hash_func User-defined hash fuction.
         * @var elem_num The total number of elements in the container.
         */
        static const int HASH_TABLE_SIZE = 611953;
        Node **head;
        Hash hash_func;
        int elem_num;

        int _rectify(const Key &key) const {
            /**
             * @brief Rectify the hash code to fit the size of the bucket.
             */
            return hash_func.hashCode(key) % HASH_TABLE_SIZE;
        }

        void _clear_nodes() {
            /*
             * @brief Free all allocated nodes in storage.
             */
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
                for (Node *np, *p = head[i]; p; p = np)
                {
                    np = p -> next;
                    delete p;
                }
        }

    public:
        class Entry;
        class Iterator;

        HashMap() { 
            /**
             * @brief Constructs an empty hash map.
             */
            head = new Node*[HASH_TABLE_SIZE];
            memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
            elem_num = 0;
            hash_func = Hash();
        }

        ~HashMap() { 
            /**
             * @brief Destructor
             */
            _clear_nodes(); 
            delete[] head;
        }

        HashMap &operator=(const HashMap &other) {
            /**
             * @brief Assignment operator
             */
            if (this != &other)
            {
                _clear_nodes();
                memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
                for (int i = 0; i < HASH_TABLE_SIZE; i++)
                {
                    for (Node *p = other.head[i]; p; p = p -> next)
                    {
                        Node *tmp_ptr = new Node(p -> key, p -> val, head[i]);
                        head[i] = tmp_ptr;
                    }
                }
                elem_num = other.elem_num;
                hash_func = other.hash_func;
            }
            return *this;
        }

        HashMap(const HashMap &other) {
            /**
             * @brief Copy-constructor
             */
            head = new Node*[HASH_TABLE_SIZE];
            memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
            {
                for (Node *p = other.head[i]; p; p = p -> next)
                {
                    Node *tmp_ptr = new Node(p -> key, p -> val, head[i]);
                    head[i] = tmp_ptr;
                }
            }
            elem_num = other.elem_num;
            hash_func = other.hash_func;
        }

        Iterator iterator() const { return Iterator(this); }
        // @brief Returns an iterator over the elements in this map.

        void clear() {
            /**
             * @brief Removes all of the mappings from this map.
             */
            _clear_nodes();
            memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
            elem_num = 0;
        }

        bool containsKey(const Key &key) const {
            /**
             * @brief Returns true if this map contains a mapping for the specified
             * key.
             */
            for (Node *p = head[_rectify(key)]; p; p = p -> next)
                if (p -> key == key) return true;
            return false;
        }

        bool containsValue(const Val &value) const {
            /**
             * @brief Returns true if this map maps one or more keys to the
             * specified value.
             */
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
                for (Node *p = head[i]; p; p = p -> next)
                    if (p -> val == value) return true;
            return false;
        }

        const Val &get(const Key &key) const {
            /**
             * @brief Returns a const reference to the value to which the specified
             * key is mapped.  If the key is not present in this map, this function
             * should throw ElementNotExist exception.
             * @throw ElementNotExist
             */

            for (Node *p = head[_rectify(key)]; p; p = p -> next)
                if (p -> key == key) return p -> val;
            throw ElementNotExist();
        }

        bool isEmpty() const { return elem_num == 0; }
        // @brief Returns true if this map contains no key-value mappings.

        void put(const Key &key, const Val &value) {
            /**
             * @brief Associates the specified value with the specified key in this
             * map.
             */
            Node *dup = NULL;
            int hv = _rectify(key);
            for (Node *p = head[hv]; p; p = p -> next)
                if (p -> key == key) { dup = p; break; }
            if (dup == NULL) 
            {
                Node *tmp_ptr = new Node(key, value, head[hv]);
                head[hv] = tmp_ptr;
                elem_num++;
            }
            else dup -> val = value; // alter the original value
        }

        void remove(const Key &key) {
            /**
             * @brief Removes the mapping for the specified key from this map if
             * present.  If there is no mapping for the specified key, throws
             * ElementNotExist exception.
             * @throw ElementNotExist
             */
            int hv = _rectify(key);
            if (head[hv])
            {
                if (head[hv] -> key == key)
                {
                    Node *np = head[hv] -> next;
                    delete head[hv];
                    head[hv] = np;
                    elem_num--;
                    return;
                }
                else
                {
                    for (Node *p = head[hv]; p -> next; p = p -> next)
                        if (p -> next -> key == key)
                        {
                            Node *np = p -> next -> next;
                            delete p -> next;
                            p -> next = np;
                            elem_num--;
                            return;
                        }
                }
            }
            throw ElementNotExist();
        }

        int size() const { return elem_num; }
        // @brief Returns the number of key-value mappings in this map.
};

template <class Key, class Val, class Hash>
struct HashMap<Key, Val, Hash>::Node {
    Key key;
    Val val;
    Node *next;
    Node(Key _key, Val _val, Node *_next) : 
        key(_key), val(_val), next(_next) {}
};

template <class Key, class Val, class Hash>
class HashMap<Key, Val, Hash>::Entry {
    Key key;
    Val value;
    public:
    Entry(Key k, Val v)
    {
        key = k;
        value = v;
    }

    Key getKey() const
    {
        return key;
    }

    Val getValue() const
    {
        return value;
    }
};

template <class Key, class Val, class Hash>
class HashMap<Key, Val, Hash>::Iterator {
    private:
        /**
         * @var cur_index The current index of the head array to which the
         * iterator is pointing.
         * @var cur_node The current node pointer.
         * @var container Reflect pointer to the container to which it applies.
         */
        int cur_index;
        Node *cur_node;
        const HashMap *container;

        bool _try_next(int &next_index, Node * &next_node) {
            next_index = cur_index;
            next_node = cur_node;
            if (next_index < 0) 
            {
                next_index = 0;
                next_node = container -> head[0];
            } 
            else next_node = next_node -> next;
            if (next_node == NULL)
            {
                while (container -> head[++next_index] == NULL && 
                        next_index < HashMap::HASH_TABLE_SIZE);
                if (next_index < HashMap::HASH_TABLE_SIZE)
                    next_node = container -> head[next_index];
            }
            return next_node != NULL;
        }

    public:
        Iterator() {}
        Iterator(const HashMap *con) {
            container = con;
            cur_index = -1;
            cur_node = NULL;
        }
        bool hasNext() {
            /**
             * @brief Returns true if the iteration has more elements.
             */

            int nidx;
            Node *nnode;
            return _try_next(nidx, nnode);
        }

        Entry next() {
            /**
             * @brief Returns the next element in the iteration.
             * @throw ElementNotExist exception when hasNext() == false
             */

            int nidx;
            Node *nnode;
            if (!_try_next(nidx, nnode)) throw ElementNotExist();
            cur_index = nidx;
            cur_node = nnode;
            return Entry(nnode -> key, nnode -> val);
        }
};

#endif
