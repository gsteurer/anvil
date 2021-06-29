#pragma once
#include "anvil/containers/hash.h"
#include "anvil/containers/list.h"
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

/*
    // https://stackoverflow.com/questions/18670530/properly-overloading-bracket-operator-for-hashtable-get-and-set
    // https://stackoverflow.com/questions/36510763/c-thread-safe-bracket-operator-proxy
    // https://stackoverflow.com/questions/994488/what-is-proxy-class-in-c
    // https://en.wikipedia.org/wiki/Proxy_pattern

*/

// https://en.wikipedia.org/wiki/Hash_table
template <typename K, typename V>
struct Map {
   public:
    struct Proxy {  // the proxy pattern lets use overload the bracket operator on map correctly
        Map<K, V>& map;
        K key;
        Proxy(Map<K, V>& map, K key);
        // https://stackoverflow.com/questions/1010539/changing-return-type-of-a-function-without-template-specialization-c
        operator Option<V>() const;
        operator V() const = delete;  // use 'Option<V> foo =' instead 'Foo ='
        Proxy& operator=(V const& opt);
    };

    Map();
    // @@@ TODO Map(const Map<K, V>& m);
    // @@@ TODO Map<K,V>& operator(const Map<K,V> &m);
    ~Map();
    f64_t LoadFactor() const;
    f64_t Threshold() const;
    isize_t Capacity() const;
    isize_t Size() const;
    // @@@ need function to set load factor threshold
    /*
        When an insert is made such that the number of entries in a hash table exceeds the product of the load factor and the current capacity then the hash table will need to be rehashed.[9] Rehashing includes increasing the size of the underlying data structure[9] and mapping existing items to new bucket locations
        To limit the proportion of memory wasted due to empty buckets, some implementations also shrink the size of the table—followed by a rehash—when items are deleted.
    */
    void Rehash(isize_t size);
    // the average cost of a lookup depends only on the average number of keys per bucket—that is, it is roughly proportional to the load factor.
    // a chained hash table with 1000 slots and 10,000 stored keys (load factor 10) is five to ten times slower than a 10,000-slot table (load factor 1); but still 1000 times faster than a plain sequential list.
    Proxy operator[](const K& key);
    Option<V> operator[](const K& key) const;
    isize_t IndexOf(K key) const;
    // https://stackoverflow.com/questions/18670530/properly-overloading-bracket-operator-for-hashtable-get-and-set
    bool Insert(K key, V value);
    Option<V> Remove(K key);
    void Clear();

    // let's store collisions in a linked list
    // @@@ when an item is added to a bucket, compute its size; store max size.
    // according to the birthday problem there is approximately a 95% (for n = 2450?, buckets = 1mill) chance of at least two of the keys being hashed to the same slot.

   private:
    struct Node {
        Node() {}
        Node(K key, V value);
        ~Node() {}
        K key;
        V value;
        bool operator==(const Node& rhs) const;
        bool operator!=(const Node& rhs) const;
    };

    List<Node>* m_data;  // @@@ make this an array of poisize_ters to Lists to reduce size
    void Tick();
    isize_t m_size;                         // number of items
    isize_t m_capacity;                     // number of buckets
    f64_t m_load_factor_threshold = 0.75f;  // when the threshold is passed, we need to resize the map
};

// As the load factor grows larger, the hash table becomes slower,
// The expected constant time property of a hash table assumes that the load factor be kept below some boun
// the default load factor for a HashMap in Java 10 is 0.75, which "offers a good trade-off between time and space costs.
// As the load factor approaches 0, the proportion of unused areas in the hash table increases. This results in wasted memory.

template <typename K, typename V>
Map<K, V>::Map() {
    m_capacity = 16;
    m_size = 0;
    m_data = new List<Node>[m_capacity];
}

template <typename K, typename V>
Map<K, V>::~Map() {
    delete[] m_data;
}

template <typename K, typename V>
f64_t Map<K, V>::LoadFactor() const {
    return static_cast<f64_t>(m_size) / static_cast<f64_t>(m_capacity);
}

template <typename K, typename V>
f64_t Map<K, V>::Threshold() const {
    return m_load_factor_threshold;
}

template <typename K, typename V>
isize_t Map<K, V>::Capacity() const {
    return m_capacity;
}

template <typename K, typename V>
isize_t Map<K, V>::Size() const {
    return m_size;
}

template <typename K, typename V>
void Map<K, V>::Rehash(isize_t size) {
    // size must be a power of 2
    if (!((size & (size - 1)) == 0)) {
        return;
    }
    List<Node>* new_data = new List<Node>[size];
    for (isize_t idx = 0; idx < m_capacity; idx++) {
        for (isize_t jdx = 0; jdx < m_data[idx].Length(); jdx++) {
            Node node = m_data[idx][jdx];
            long hash = Hashable<K>::Hash(node.key);
            isize_t index = hash & size - 1;
            new_data[index].PushFront(node);
        }
    }
    List<Node>* previous = m_data;
    m_data = new_data;
    m_capacity = size;
    delete[] previous;
}

template <typename K, typename V>
typename Map<K, V>::Proxy Map<K, V>::operator[](const K& key) {
    return Proxy(*this, key);
}

template <typename K, typename V>
Option<V> Map<K, V>::operator[](const K& key) const {
    Option<V> result;
    isize_t map_index = IndexOf(key);
    List<Node>* node_list = &(m_data[map_index]);

    for (isize_t idx = 0; idx < node_list->Length(); idx++) {
        Node* node = &(*node_list)[idx];
        if (node->key == key) {
            result.result = Option<V>::Some;
            result.value = node->value;
            return result;
        }
    }

    return result;
}

template <typename K, typename V>
isize_t Map<K, V>::IndexOf(K key) const {
    long hash = Hashable<K>::Hash(key);
    return hash & m_capacity - 1;
}

template <typename K, typename V>
bool Map<K, V>::Insert(K key, V value) {
    isize_t index = IndexOf(key);
    Node node(key, value);
    List<Node>* node_list = &(m_data[index]);

    for (isize_t idx = 0; idx < node_list->Length(); idx++) {
        Node* node = &(*node_list)[idx];
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

    isize_t map_index = IndexOf(key);
    List<Node>* node_list = &(m_data[map_index]);
    for (isize_t idx = 0; idx < node_list->Length(); idx++) {
        Node* node = &(*node_list)[idx];
        if (node->key == key) {
            Option<Node> item = m_data[map_index].RemoveAt(idx);
            result.result = Option<V>::Some;
            result.value = item.value.value;
            m_size--;
            return result;
        }
    }

    return result;
}

template <typename K, typename V>
void Map<K, V>::Clear() {
    m_capacity = 16;
    m_size = 0;
    delete[] m_data;
    m_data = new List<Node>[m_capacity];
}

template <typename K, typename V>
void Map<K, V>::Tick() {
    if (this->LoadFactor() > this->Threshold()) {
        this->Rehash(m_capacity * 2);
    }
}

template <typename K, typename V>
Map<K, V>::Node::Node(K key, V value) : key(key), value(value) {
}

template <typename K, typename V>
bool Map<K, V>::Node::operator==(const Node& rhs) const {
    return this->key == rhs.key;
}

template <typename K, typename V>
bool Map<K, V>::Node::operator!=(const Node& rhs) const {
    return !(this->key == rhs.key);
}

template <typename K, typename V>
Map<K, V>::Proxy::Proxy(Map<K, V>& map, K key) : map(map), key(key) {
}
// https://stackoverflow.com/questions/1010539/changing-return-type-of-a-function-without-template-specialization-c

template <typename K, typename V>
Map<K, V>::Proxy::operator Option<V>() const {  // this is a conversion function
    const Map<K, V>* m = &map;
    return m->operator[](key);
}

template <typename K, typename V>
typename Map<K, V>::Proxy& Map<K, V>::Proxy::operator=(V const& opt) {
    map.Insert(key, opt);
    return *this;
}

}  // namespace containers
}  // namespace anvil