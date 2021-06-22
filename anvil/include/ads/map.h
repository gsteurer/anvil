#pragma once
#include "ads/hash.h"
#include "ads/list.h"
#include "option.h"

template <typename K, typename V>
struct MapNode {
    MapNode() {}
    MapNode(K key, V value) : key(key), value(value) {}
    ~MapNode() {}
    K key;
    V value;
    bool operator==(const MapNode<K, V>& rhs) const {
        return this->key == rhs.key;
    }
    bool operator!=(const MapNode<K, V>& rhs) const {
        return !(this->key == rhs.key);
    }
};

template <typename K, typename V>
struct Map;

template <typename K, typename V>

/*
    // https://stackoverflow.com/questions/18670530/properly-overloading-bracket-operator-for-hashtable-get-and-set
    // https://stackoverflow.com/questions/36510763/c-thread-safe-bracket-operator-proxy
    // https://stackoverflow.com/questions/994488/what-is-proxy-class-in-c
    // https://en.wikipedia.org/wiki/Proxy_pattern

*/
struct MapProxy {  // this is the proxy pattern

    Map<K, V>& map;
    K key;
    MapProxy(Map<K, V>& map, K key) : map(map), key(key) {}
    // https://stackoverflow.com/questions/1010539/changing-return-type-of-a-function-without-template-specialization-c
    operator Option<V>() const {  // this is a conversion function
        Option<V> result;
        int map_index = map.IndexOf(key);
        List<MapNode<K, V>>* node_list = &(map.m_data[map_index]);

        for (int idx = 0; idx < node_list->Length(); idx++) {
            MapNode<K, V>* node = &(*node_list)[idx];
            if (node->key == key) {
                result.result = Option<V>::Some;
                result.value = node->value;
                return result;
            }
        }
        return result;
    }

    operator V() const = delete;  // use 'Option<V> foo =' instead 'Foo ='

    MapProxy&
    operator=(V const& opt) {
        map.Insert(key, opt);
        return *this;
    }
};

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
    MapProxy<K, V> operator[](const K& key);
    // https://stackoverflow.com/questions/18670530/properly-overloading-bracket-operator-for-hashtable-get-and-set
    bool Insert(K key, V value);
    Option<V> Remove(K key);
    int IndexOf(K key) const;

    // let's store collisions in a linked list
    // @@@ when an item is added to a bucket, compute its size; store max size.
    // according to the birthday problem there is approximately a 95% (for n = 2450?, buckets = 1mill) chance of at least two of the keys being hashed to the same slot.
    List<MapNode<K, V>>* m_data;  // @@@ make this an array of pointers to Lists to reduce size
    void Tick();
    float Threshold() const;
    int Capacity() const;
    int Size() const;
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
    m_capacity = 16;
    m_size = 0;
    m_data = new List<MapNode<K, V>>[m_capacity];
}

template <typename K, typename V>
Map<K, V>::~Map() {
    delete[] m_data;
}

template <typename K, typename V>
Map<K, V>::Map(const Map<K, V>& m) {
}

template <typename K, typename V>
float Map<K, V>::LoadFactor() {
    return static_cast<float>(m_size) / static_cast<float>(m_capacity);
}

template <typename K, typename V>
int Map<K, V>::IndexOf(K key) const {
    long hash = Hashable<K>::Hash(key);
    return hash & m_capacity - 1;
}

template <typename K, typename V>
void Map<K, V>::Tick() {
    if (this->LoadFactor() > this->Threshold()) {
        this->Rehash(m_capacity * 2);
    }
}

template <typename K, typename V>
float Map<K, V>::Threshold() const {
    return m_load_factor_threshold;
}

template <typename K, typename V>
int Map<K, V>::Capacity() const {
    return m_capacity;
}

template <typename K, typename V>
int Map<K, V>::Size() const {
    return m_size;
}

template <typename K, typename V>
void Map<K, V>::Rehash(int size) {
    // size must be a power of 2
    if (!((size & (size - 1)) == 0)) {
        return;
    }
    List<MapNode<K, V>>* new_data = new List<MapNode<K, V>>[size];
    for (int idx = 0; idx < m_capacity; idx++) {
        for (int jdx = 0; jdx < m_data[idx].Length(); jdx++) {
            MapNode<K, V> node = m_data[idx][jdx];
            long hash = Hashable<K>::Hash(node.key);
            int index = hash & size - 1;
            new_data[index].PushFront(node);
        }
    }
    List<MapNode<K, V>>* previous = m_data;
    m_data = new_data;
    m_capacity = size;
    delete[] previous;
}

template <typename K, typename V>
MapProxy<K, V> Map<K, V>::operator[](const K& key) {
    return MapProxy(*this, key);
}

template <typename K, typename V>
bool Map<K, V>::Insert(K key, V value) {
    int index = IndexOf(key);
    MapNode<K, V> node(key, value);
    List<MapNode<K, V>>* node_list = &(m_data[index]);

    for (int idx = 0; idx < node_list->Length(); idx++) {
        MapNode<K, V>* node = &(*node_list)[idx];
        if (node->key == key) {
            return false;
        }
    }
    m_data[index].PushFront(node);
    m_size++;
    this->Tick();
    return true;
}

template <typename K, typename V>
Option<V> Map<K, V>::Remove(K key) {
    Option<V> result;
    result.result = Option<V>::None;

    int map_index = IndexOf(key);
    List<MapNode<K, V>>* node_list = &(m_data[map_index]);
    for (int idx = 0; idx < node_list->Length(); idx++) {
        MapNode<K, V>* node = &(*node_list)[idx];
        if (node->key == key) {
            Option<MapNode<K, V>> item = m_data[map_index].RemoveAt(idx);
            result.result = Option<V>::Some;
            result.value = item.value.value;
            m_size--;
            return result;
        }
    }

    return result;
}