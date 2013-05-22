/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"
#include <cstring>

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument Hash are used to specify the hash function.
 * Hash should be a class with a static function named ``hashCode'',
 * which takes a parameter of type Key and returns a value of type int.
 * For example, the following class
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
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */

template <class Key, class Val, class Hash>
class HashMap
{
    private:
        struct Node;
        static const int HASH_TABLE_SIZE = 611953;
        Node **head;
        Hash hash_func;
        int elem_num;

        int _rectify(const Key &key) const {
            return hash_func.hashCode(key) % HASH_TABLE_SIZE;
        }

        void _clear_nodes() {
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
        /**
         * TODO Constructs an empty hash map.
         */
        HashMap() { 
            head = new Node*[HASH_TABLE_SIZE];
            memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
            elem_num = 0;
            hash_func = Hash();
        }

        /**
         * TODO Destructor
         */
        ~HashMap() { 
            _clear_nodes(); 
            delete[] head;
        }

        /**
         * TODO Assignment operator
         */
        HashMap &operator=(const HashMap &other) {
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
            return *this;
        }

        /**
         * TODO Copy-constructor
         */
        HashMap(const HashMap &other) {
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

        /**
         * TODO Returns an iterator over the elements in this map.
         */
        Iterator iterator() const { return Iterator(this); }

        /**
         * TODO Removes all of the mappings from this map.
         */
        void clear() {
            _clear_nodes();
            memset(head, 0, sizeof(Node*) * HASH_TABLE_SIZE);
            elem_num = 0;
        }

        /**
         * TODO Returns true if this map contains a mapping for the specified key.
         */
        bool containsKey(const Key &key) const {
            for (Node *p = head[_rectify(key)]; p; p = p -> next)
                if (p -> key == key) return true;
            return false;
        }

        /**
         * TODO Returns true if this map maps one or more keys to the specified value.
         */
        bool containsValue(const Val &value) const {
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
                for (Node *p = head[i]; p; p = p -> next)
                    if (p -> val == value) return true;
            return false;
        }

        /**
         * TODO Returns a const reference to the value to which the specified key is mapped.
         * If the key is not present in this map, this function should throw ElementNotExist exception.
         * @throw ElementNotExist
         */
        const Val &get(const Key &key) const {
            for (Node *p = head[_rectify(key)]; p; p = p -> next)
                if (p -> key == key) return p -> val;
            throw ElementNotExist();
        }

        /**
         * TODO Returns true if this map contains no key-value mappings.
         */
        bool isEmpty() const { return elem_num == 0; }

        /**
         * TODO Associates the specified value with the specified key in this map.
         */
        void put(const Key &key, const Val &value) {
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

        /**
         * TODO Removes the mapping for the specified key from this map if present.
         * If there is no mapping for the specified key, throws ElementNotExist exception.
         * @throw ElementNotExist
         */
        void remove(const Key &key) {
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

        /**
         * TODO Returns the number of key-value mappings in this map.
         */
        int size() const { return elem_num; }
};

template <class Key, class Val, class Hash>
struct HashMap<Key, Val, Hash>::Node {
    Key key;
    Val val;
    Node *next;
    Node(Key _key, Val _val, Node *_next) : key(_key), val(_val), next(_next) {}
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
            } else next_node = next_node -> next;
            if (next_node == NULL)
            {
                while (container -> head[++next_index] == NULL && next_index < HashMap::HASH_TABLE_SIZE);
                if (next_index < HashMap::HASH_TABLE_SIZE)
                    next_node = container -> head[next_index];
            }
            return next_node != NULL;
        }

    public:
        Iterator(const HashMap *con) {
            container = con;
            cur_index = -1;
            cur_node = NULL;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            int nidx;
            Node *nnode;
            return _try_next(nidx, nnode);
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        Entry next() {
            int nidx;
            Node *nnode;
            if (!_try_next(nidx, nnode)) throw ElementNotExist();
            cur_index = nidx;
            cur_node = nnode;
            return Entry(nnode -> key, nnode -> val);
        }
};

#endif
