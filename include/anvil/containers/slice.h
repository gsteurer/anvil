#pragma once

#include "anvil/containers/arrayutils.h"
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

template <typename T>
struct Slice {
    Slice();
    ~Slice();
    Slice(const Slice<T>& slice);
    Slice<T>& operator=(const Slice<T>& slice);
    // length -> number of items in the Slice
    // capacity -> total number of items the Slice can contain before it is resized
    // @@@ TODO Slice(isize_t length, isize_t capacity);

    isize_t Length() const;
    isize_t Capacity() const;
    Option<isize_t> IndexOf(T item)const;
    const T operator[](isize_t index) const;
    
    T& operator[](isize_t index);
    void Insert(T);
    T Remove(isize_t index);
    void Clear();
    Slice<T> GetSlice(isize_t start, isize_t end);

   private:
    void Resize(isize_t size);
    isize_t m_capacity;
    isize_t m_size;
    T** m_data;
};

template <typename T>
Slice<T>::Slice() {
    m_capacity = 16;
    m_size = 0;
    m_data = new T*[m_capacity];
    for (isize_t idx = 0; idx < m_capacity; idx++) {
        m_data[idx] = new T();
    }
}

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
Slice<T>::Slice(const Slice<T>& slice) : Slice() {
    for (isize_t idx = 0; idx < slice.Length(); idx++) {
        const T val = slice[idx];
        this->Insert(val);
    }
}
template <typename T>
Slice<T>& Slice<T>::operator=(const Slice<T>& slice) {
    
    this->Clear();
    for (isize_t idx = 0; idx < slice.Length(); idx++) {
        const T val = slice[idx];
        this->Insert(val);
    }

    return *this;
}

template <typename T>
isize_t Slice<T>::Length() const {
    return m_size;
}

template <typename T>
isize_t Slice<T>::Capacity() const {
    return m_capacity;
}

template <typename T>
const T Slice<T>::operator[](isize_t index) const {
    return *(m_data[index]);
}

template <typename T>
Option<isize_t> Slice<T>::IndexOf(T item) const {
    return search<Slice<T>, T>(*this, Length(), item);
}

template <typename T>
T& Slice<T>::operator[](isize_t index) {
    // @@@ TODO FIXME; needs to resize or error when out of bounds
    return *(m_data[index]);
}

template <typename T>
void Slice<T>::Resize(isize_t size) {
    T** m_previous = m_data;
    m_data = new T*[size];
    m_capacity = size;
    if (size < m_size) {
        for (isize_t idx = size; idx < m_size; idx++) {
            delete m_previous[idx];
        }
        m_size = size;
    }
    for (isize_t idx = 0; idx < m_capacity; idx++) {
        if (idx < m_size) {
            m_data[idx] = m_previous[idx];
        } else {
            m_data[idx] = new T();
        }
    }
    delete[] m_previous;
}

template <typename T>
void Slice<T>::Insert(T item) {
    if (m_size == m_capacity) {
        Resize(m_capacity * 2);
    }
    *(m_data[m_size]) = T(item);
    m_size++;
}

template <typename T>
T Slice<T>::Remove(isize_t index) {
    T result = *(m_data[index]);
    delete m_data[index];
    for (isize_t idx = index + 1; idx < m_size; idx++) {
        m_data[idx - 1] = m_data[idx];
    }
    m_data[m_size - 1] = new T();
    m_size--;

    return result;
}

template <typename T>
void Slice<T>::Clear() {
    m_size = 0;
}


template <typename T>
Slice<T> Slice<T>::GetSlice(isize_t start, isize_t end) {
    Slice<T> ret;
    for (isize_t idx = start; idx < end && idx < m_size && idx > 0; idx++) {
        const T val = *m_data[idx];
        ret.Insert(val);
    }
    return ret;
}

/*
// @@@ TODO
template <typename T>
void append(Slice<T> Slice, T data) {
}
*/

}  // namespace containers
}  // namespace anvil
