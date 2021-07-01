#pragma once

#include "anvil/containers/redblacktree.h"
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

template <typename K, typename V>
struct SortedMap {
    struct Proxy {
        SortedMap<K, V>& map;
        K key;
        Proxy(SortedMap<K, V>& map, K key);
        operator Option<V>() const;
        operator V() const = delete;
        Proxy& operator=(V const& opt);
    };

    SortedMap();
    ~SortedMap();
    isize_t Size() const;

    Proxy operator[](const K& key);
    Option<V> operator[](const K& key) const;
    bool Insert(K key, V value);
    Option<V> Remove(K key);
    void Clear();

   private:
    struct Node {
        Node();
        Node(K key, V value);
        ~Node() {}
        K key;
        V value;
        bool operator==(const Node& rhs) const;
        bool operator!=(const Node& rhs) const;
        bool operator<(const Node& rhs) const;
    };
    RBTree<Node> m_data;
    isize_t m_size;
};

template <typename K, typename V>
SortedMap<K, V>::SortedMap() {
    m_size = 0;
}

template <typename K, typename V>
SortedMap<K, V>::~SortedMap() {
    Clear();
}

template <typename K, typename V>
isize_t SortedMap<K, V>::Size() const {
    return m_size;
}

template <typename K, typename V>
typename SortedMap<K, V>::Proxy SortedMap<K, V>::operator[](const K& key) {
    return Proxy(*this, key);
}

template <typename K, typename V>
Option<V> SortedMap<K, V>::operator[](const K& key) const {
    Option<Node> item = m_data.Search(Node(key, V()));
    Option<V> result;
    if (item.result == Option<Node>::Some) {
        result.result = Option<V>::Some;
        result.value = item.value.value;
    }

    return result;
}

template <typename K, typename V>
bool SortedMap<K, V>::Insert(K key, V value) {
    Option<Node> result = m_data.Search(Node(key, V()));
    if (result.result == Option<Node>::None) {
        m_data.Insert(Node(key, value));
        m_size++;
        return true;
    }
    return false;
}

template <typename K, typename V>
Option<V> SortedMap<K, V>::Remove(K key) {
    Option<Node> item = m_data.Delete(Node(key, V()));
    Option<V> result;

    if (item.result == Option<Node>::Some) {
        result.result = Option<V>::Some;
        result.value = item.value.value;
        m_size--;
    }

    return result;
}

template <typename K, typename V>
void SortedMap<K, V>::Clear() {
    m_data.Clear();
    m_size = 0;
}

template <typename K, typename V>
SortedMap<K, V>::Node::Node() {
}

template <typename K, typename V>
SortedMap<K, V>::Node::Node(K key, V value) : key(key), value(value) {
}

template <typename K, typename V>
bool SortedMap<K, V>::Node::operator==(const Node& rhs) const {
    return key == rhs.key;
}

template <typename K, typename V>
bool SortedMap<K, V>::Node::operator!=(const Node& rhs) const {
    return key != rhs.key;
}

template <typename K, typename V>
bool SortedMap<K, V>::Node::operator<(const Node& rhs) const {
    return key < rhs.key;
}

template <typename K, typename V>
SortedMap<K, V>::Proxy::Proxy(SortedMap<K, V>& map, K key) : map(map), key(key) {
}
// https://stackoverflow.com/questions/1010539/changing-return-type-of-a-function-without-template-specialization-c

template <typename K, typename V>
SortedMap<K, V>::Proxy::operator Option<V>() const {  // this is a conversion function
    const SortedMap<K, V>* m = &map;
    return m->operator[](key);
}

template <typename K, typename V>
typename SortedMap<K, V>::Proxy& SortedMap<K, V>::Proxy::operator=(V const& opt) {
    map.Insert(key, opt);
    return *this;
}

}  // namespace containers
}  // namespace anvil