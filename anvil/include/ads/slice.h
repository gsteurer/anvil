#pragma once

#include "ads/arrayutils.h"
#include "option.h"
#include "types.h"

namespace anvil {
template <typename T>
struct Slice {
    Slice();
    // length -> number of items in the Slice
    // capacity -> total number of items the Slice can contain before it is resized
    // @@@ TODO Slice(isize_t length, isize_t capacity);
    void Insert(T);
    // @@@ TODO T Remove(isize_t index);
    ~Slice();
    const T operator[](isize_t index) const;
    T& operator[](isize_t index);
    isize_t Length();
    isize_t Capacity();
    Option<isize_t> IndexOf(T item);

   private:
    isize_t m_capacity;
    isize_t m_length;
    T** m_data;
};

template <typename T>
isize_t Slice<T>::Length() {
    return m_length;
}

template <typename T>
isize_t Slice<T>::Capacity() {
    return m_capacity;
}

template <typename T>
Slice<T>::Slice() {
    m_capacity = 16;
    m_length = 0;
    m_data = new T*[m_capacity];
    for (isize_t idx = 0; idx < m_capacity; idx++) {
        m_data[idx] = new T();
    }
}

/*
// @@@ TODO
template <typename T>
Slice<T>::Slice(isize_t length, isize_t capacity) {
    m_capacity = capacity;
    m_length = 0;
    m_data = new T*[m_capacity];
    for (isize_t idx = 0; idx < m_capacity; idx++) {
        m_data[idx] = new T();
    }
}
*/
template <typename T>
Slice<T>::~Slice() {
    if (m_data != nullptr) {
        for (isize_t idx = 0; idx < m_capacity; idx++) {
            delete m_data[idx];
        }
        delete[] m_data;
    }
}

template <typename T>
const T Slice<T>::operator[](isize_t index) const {
    return *(m_data[index]);
}

template <typename T>
T& Slice<T>::operator[](isize_t index) {
    return *(m_data[index]);
}

template <typename T>
void Slice<T>::Insert(T item) {
    if (m_length == m_capacity) {
        T** m_previous = m_data;
        m_data = new T*[m_capacity * 2];
        m_capacity = m_capacity * 2;
        for (isize_t idx = 0; idx < m_capacity; idx++) {
            if (idx < m_length) {
                m_data[idx] = m_previous[idx];
            } else {
                m_data[idx] = new T();
            }
        }
        delete[] m_previous;
    }
    *(m_data[m_length]) = T(item);
    m_length++;
}

template <typename T>
Option<isize_t> Slice<T>::IndexOf(T item) {
    return search<Slice<T>, T>(*this, Length(), item);
}

/*
// @@@ TODO
template <typename T>
T Slice<T>::Remove(isize_t index) {
}
*/

/*
// @@@ TODO
template <typename T>
void append(Slice<T> Slice, T data) {
}
*/

}  // namespace anvil
