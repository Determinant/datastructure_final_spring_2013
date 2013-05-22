/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V>
class TreeMap
{
public:
    class Entry
    {
        K key;
        V value;
    public:
        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }
    };

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
        const Entry &next() {}
    };

    /**
     * TODO Constructs an empty tree map.
     */
    TreeMap() { }

    /**
     * TODO Destructor
     */
    ~TreeMap() { }

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x) { }

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x) { }

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const {}

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear() {}

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const {}

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const {}

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const {}

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const {}

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value) {}

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key) {}

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {}
};

#endif
