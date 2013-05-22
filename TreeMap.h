/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include "LinkedList.h"

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class Key, class Val>
class TreeMap
{
    private:
        struct Node;
        struct Seg;
        Node *root, *head;
        int elem_num;

        void _clear_nodes_dfs(Node *p) {
            if (p == NULL) return; 
            _clear_nodes_dfs(p -> ch[0]);
            _clear_nodes_dfs(p -> ch[1]);
            delete p;
        }

        void _clear_nodes() {
            _clear_nodes_dfs(root);
        }

        Seg _copy_nodes_dfs(Node **des_pptr, Node *src_ptr) {
            Node *des_ptr = *des_pptr = new Node();
            *des_ptr = *src_ptr;
            return Seg::merge(_copy_nodes_dfs(&(des_ptr -> ch[0]), src_ptr -> ch[0]),
                                des_ptr,
                            _copy_nodes_dfs(&(des_ptr -> ch[1]), src_ptr -> ch[1]));
        }

        void _copy_nodes(const TreeMap &src) {
           Seg chain = _copy_nodes_dfs(&root, src.root);
           (head -> next = chain.begin) -> prev = head;
           (head -> prev = chain.end) -> next = head;
        }

        void _rotate(register Node **pptr, bool dir) {
            register Node *ptr = *pptr, *tptr = ptr -> ch[dir];
            ptr -> ch[dir] = tptr -> ch[!dir];
            tptr -> ch[!dir] = ptr;
            *pptr = tptr;
        }

        bool _contains_value_dfs(Node *p, const Val &val) {
            if (p == NULL) return false;
            if (p -> val == val) return true;
            return _contains_value_dfs(p -> ch[0]) ||
                    _contains_value_dfs(p -> ch[1]);
        }

    public:
        class Entry;
        class Iterator;
        /**
         * TODO Constructs an empty tree map.
         */
        TreeMap() {
            root = NULL;
            head = new Node;
            elem_num = 0;
        }

        /**
         * TODO Destructor
         */
        ~TreeMap() { 
            _clear_nodes();
            delete head;
        }

        /**
         * TODO Assignment operator
         */
        TreeMap &operator=(const TreeMap &other) {
            _clear_nodes();
            _copy_nodes(other);
            elem_num = other.elem_num;
        }

        /**
         * TODO Copy-constructor
         */
        TreeMap(const TreeMap &other) {
            head = new Node;
            _copy_nodes(other);
            elem_num = other.elem_num;
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
            root = NULL;
            elem_num = 0;
        }

        /**
         * TODO Returns true if this map contains a mapping for the specified key.
         */
        bool containsKey(const Key &key) const {
            for (Node *p = root; p; p = p -> ch[key < p -> key])
                if (key == p -> key) return true;
            return false;
        }

        /**
         * TODO Returns true if this map maps one or more keys to the specified value.
         */
        bool containsValue(const Val &value) const {
            return _contains_value_dfs(root, value); 
        }

        /**
         * TODO Returns a const reference to the value to which the specified key is mapped.
         * If the key is not present in this map, this function should throw ElementNotExist exception.
         * @throw ElementNotExist
         */
        const Val &get(const Key &key) const {
            for (Node *p = root; p; p = p -> ch[key < p -> key])
                if (key == p -> key) return p -> val;
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
            Node **pptr = &root;
            Node *prv = head, *nxt = head;
            LinkedList<Node **> path;
            LinkedList<bool> drec;
            int top = -1;
            bool dir;
            for (Node *ptr; (ptr = *pptr); pptr = &(ptr -> ch[dir]))
            {
                if (key == ptr -> key)
                {
                    ptr -> val = value; // alter the value
                    return;
                }
                ((dir = key < ptr -> key) ? nxt : prv) = ptr;
                path.addLast(pptr);
                drec.addLast(dir);
            }
            Node *t = *pptr = new Node();
            t -> pri = rand();
            t -> key = key;
            t -> val = value;
            t -> ch[0] = t -> ch[1] = NULL;
            (t -> prev = prv) -> next = t;
            (t -> next = nxt) -> prev = t;
            for (; !path.isEmpty() && t -> pri < (*path.getLast()) -> pri;)
            {
                _rotate(path.getLast(), drec.getLast())
                path.removeLast();
                drec.removeLast();
            }
            elem_num++;
        }

        /**
         * TODO Removes the mapping for the specified key from this map if present.
         * If there is no mapping for the specified key, throws ElementNotExist exception.
         * @throw ElementNotExist
         */
        void remove(const Key &key) {
            Node **pptr = &root;
            for (Node *ptr;
                    (ptr = *pptr) && !(key == ptr -> key); 
                    pptr = &(ptr -> ch[key < ptr -> key]));

            Node *ptr = *pptr;
            Node * &chl = ptr -> ch[0], &chr = ptr -> ch[1]; 
            while (chl || chr)
            {
                bool dir = chr && (!chl || chr -> pri < chl -> pri);
                _rotate(pptr, dir);
                pptr = &((*pptr) -> ch[!dir]);
            }
            ptr -> prev -> next = ptr -> next;
            ptr -> next -> prev = ptr -> prev;
            delete ptr;
            *pptr = NULL;
            elem_num--;
        }

        /**
         * TODO Returns the number of key-value mappings in this map.
         */
        int size() const { return elem_num; }
};

template<class Key, class Val>
struct TreeMap<Key, Val>::Node {
    Key key;
    Val val;
    int pri;
    Node *ch[2], *prev, *next;
};

template<class Key, class Val>
struct TreeMap<Key, Val>::Seg {
    Node *begin, *end;
    Seg() : begin(NULL), end(NULL) {}
    Seg(Node *_begin, Node *_end) : begin(_begin), end(_end) {}
    static Seg merge(const Seg &a, Node *mid, const Seg &b) {
        if (a.end != NULL) (a.end -> next = mid) -> prev = a.end;
        if (b.begin != NULL) (b.begin -> prev = mid) -> next = b.begin;
        return Seg(a.end == NULL ? mid : a.begin, 
                    b.begin == NULL ? mid : b.end);
    }
};

template<class Key, class Val>
class TreeMap<Key, Val>::Entry {
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

template<class Key, class Val>
class TreeMap<Key, Val>::Iterator {
    private:
        Node *container, *cursor;
    public:
        Iterator(const TreeMap *con) : con(container), cursor(container -> head) {}
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            return cursor -> next == container -> head;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        Entry next() {
            if (!hasNext()) throw ElementNotExist();
            cursor = cursor -> next;
            return Entry(cursor -> key, cursor -> val);
        }
};

#endif
