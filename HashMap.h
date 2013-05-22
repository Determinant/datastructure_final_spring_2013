/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
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
template <class K, class V, class H>
class HashMap
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
     * TODO Constructs an empty hash map.
     */
    HashMap() { }

    /**
     * TODO Destructor
     */
    ~HashMap() { }

    /**
     * TODO Assignment operator
     */
    HashMap &operator=(const HashMap &x) { }

    /**
     * TODO Copy-constructor
     */
    HashMap(const HashMap &x) { }

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
