#pragma once
#include <cstdlib>

#include "option.h"

template <typename T>
void scramble(T& array, unsigned int size, unsigned int repeat_count = 1) {
    for (int count = 0; count < repeat_count; count++) {
        for (int idx = 0; idx < size; idx++) {
            unsigned int jdx = std::rand() % size;
            unsigned int kdx = std::rand() % size;
            auto tmp = array[jdx];
            array[jdx] = array[kdx];
            array[kdx] = tmp;
        }
    }
}

template <typename T>
void sort(T& array, unsigned int size) {
}

template <typename T>
void quicksort(T& array, int lo, int hi) {
    if (lo < hi) {
        int p = _partition(array, lo, hi);
        quicksort(array, lo, p - 1);
        quicksort(array, p + 1, hi);
    }
}

template <typename T>
int _partition(T& array, int lo, int hi) {
    auto pivot = array[hi];
    int i = lo;
    for (int j = lo; j < hi; j++) {
        if (array[j] < pivot) {
            auto tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i = i + 1;
        }
    }
    auto tmp = array[i];
    array[i] = array[hi];
    array[hi] = tmp;
    return i;
}

template <typename T, typename U>
Option<unsigned int> search(T& array, unsigned int size, U item) {
    Option<unsigned int> result;
    for (unsigned int idx = 0; idx < size; idx++) {
        if (array[idx] == item) {
            result.result = Option<unsigned int>::Some;
            result.value = idx;
            return result;  // {.value = idx, .result = Option<unsigned int>::Some};
        }
    }
    result.result = Option<unsigned int>::None;
    return result;  // {.result = Option<unsigned int>::None};
}

template <typename T>
struct Slice {
    Slice();
    // length -> number of items in the Slice
    // capacity -> total number of items the Slice can contain before it is resized
    Slice(unsigned int length, unsigned int capacity);
    void Insert(T);
    T Remove(unsigned int index);
    ~Slice();
    const T operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    unsigned int Length();
    unsigned int Capacity();
    Option<unsigned int> IndexOf(T item);

   private:
    unsigned int m_capacity;
    unsigned int m_length;
    T** m_data;
};

template <typename T>
unsigned int Slice<T>::Length() {
    return m_length;
}

template <typename T>
unsigned int Slice<T>::Capacity() {
    return m_capacity;
}

template <typename T>
Slice<T>::Slice() : Slice(0, 16) {}

template <typename T>
Slice<T>::Slice(unsigned int length, unsigned int capacity) {
    m_capacity = capacity;
    m_length = 0;
    m_data = new T*[m_capacity];
    for (int idx = 0; idx < m_capacity; idx++) {
        m_data[idx] = new T();
    }
}

template <typename T>
Slice<T>::~Slice() {
    if (m_data != nullptr) {
        for (int idx = 0; idx < m_capacity; idx++) {
            // delete m_data[idx];
        }
        delete[] m_data;
    }
}

template <typename T>
const T Slice<T>::operator[](unsigned int index) const {
    return *(m_data[index]);
}

template <typename T>
T& Slice<T>::operator[](unsigned int index) {
    return *(m_data[index]);
}

template <typename T>
void Slice<T>::Insert(T item) {
    if (m_length == m_capacity) {
        T** m_previous = m_data;
        m_data = new T*[m_capacity * 2];
        m_capacity = m_capacity * 2;
        for (unsigned int idx = 0; idx < m_capacity; idx++) {
            idx < m_length ? m_data[idx] = m_previous[idx] : m_data[idx] = new T();
        }
        delete[] m_previous;
    }
    m_data[m_length] = new T(item);
    m_length++;
}

template <typename T>
Option<unsigned int> Slice<T>::IndexOf(T item) {
    return search<Slice<T>, T>(*this, Length(), item);
}

template <typename T>
T Slice<T>::Remove(unsigned int index) {
}

template <typename T>
void append(Slice<T> Slice, T data) {
}
