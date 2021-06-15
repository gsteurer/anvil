#pragma once
#include <ads/list.h>

#include "option.h"

// https://en.cppreference.com/w/cpp/language/template_specialization

// @@@ this is wrong
template <typename T>
long Hash(T key){

};

// @@@ this is wrong
template <typename>
long Hash(int key) {
    return 55;
}

// https://en.wikipedia.org/wiki/Hash_table
template <typename K, typename V>
struct Map {
    Map();
    Map(const Map<K, V>& m);
    ~Map();
    float LoadFactor();
    // @@@ need function to set load factor threshold
    /*
        When an insert is made such that the number of entries in a hash table exceeds the product of the load factor and the current capacity then the hash table will need to be rehashed.[9] Rehashing includes increasing the size of the underlying data structure[9] and mapping existing items to new bucket locations
        To limit the proportion of memory wasted due to empty buckets, some implementations also shrink the size of the table—followed by a rehash—when items are deleted.
    */
    void Rehash(int size);
    // the average cost of a lookup depends only on the average number of keys per bucket—that is, it is roughly proportional to the load factor.
    // a chained hash table with 1000 slots and 10,000 stored keys (load factor 10) is five to ten times slower than a 10,000-slot table (load factor 1); but still 1000 times faster than a plain sequential list.
    // @@@ const Option<V> operator[](int index) const;
    const V operator[](int index) const;
    // @@@ Option<V&> operator[](int index);
    V& operator[](int index);
    void Insert(K key, V value);
    V Remove(K key);

   private:
    // let's store collisions in a linked list
    // @@@ when an item is added to a bucket, compute its size; store max size.
    // according to the birthday problem there is approximately a 95% (for n = 2450?, buckets = 1mill) chance of at least two of the keys being hashed to the same slot.
    List<V>* m_data;
    int m_size;                             // number of items
    int m_capacity;                         // number of buckets
    float m_load_factor_threshold = 0.75f;  // when the threshold is passed, we need to resize the map
};

// As the load factor grows larger, the hash table becomes slower,
// The expected constant time property of a hash table assumes that the load factor be kept below some boun
// the default load factor for a HashMap in Java 10 is 0.75, which "offers a good trade-off between time and space costs.
// As the load factor approaches 0, the proportion of unused areas in the hash table increases. This results in wasted memory.

template <typename K, typename V>
Map<K, V>::Map() {
}

template <typename K, typename V>
Map<K, V>::~Map() {
}

template <typename K, typename V>
Map<K, V>::Map(const Map<K, V>& m) {
}

template <typename K, typename V>
float Map<K, V>::LoadFactor() {
    return static_cast<float>(m_size) / static_cast<float>(m_capacity);
}

template <typename K, typename V>
void Map<K, V>::Rehash(int size) {
}

template <typename K, typename V>
const V Map<K, V>::operator[](int index) const {
}

template <typename K, typename V>
V& Map<K, V>::operator[](int index) {
}

template <typename K, typename V>
void Map<K, V>::Insert(K key, V value) {
    Hash(key);
}

template <typename K, typename V>
V Map<K, V>::Remove(K key) {
}