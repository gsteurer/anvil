#pragma once
#include "anvil/math/rand.h"
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

namespace internal {

// CREDIT: Introduction to Algorithms, 3rd Edition

inline isize_t _parent(isize_t idx) { return idx / 2; }
inline isize_t _left(isize_t idx) { return 2 * idx + 1; }
inline isize_t _right(isize_t idx) { return 2 * idx + 2; }

template <typename T>
inline void _max_heapify(T& array, isize_t heap_size, isize_t idx) {
    isize_t left = _left(idx);
    isize_t right = _right(idx);
    isize_t largest = idx;
    if (left < heap_size && array[left] > array[largest]) {
        largest = left;
    }
    if (right < heap_size && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != idx) {
        auto tmp = array[idx];
        array[idx] = array[largest];
        array[largest] = tmp;
        _max_heapify(array, heap_size, largest);
    }
}

template <typename T>
inline void _build_max_heap(T& array, isize_t heap_size) {
    for (isize_t idx = heap_size / 2 - 1; idx >= 0; idx--) {
        _max_heapify(array, heap_size, idx);
    }
}

template <typename T>
inline void _min_heapify(T& array, isize_t heap_size, isize_t idx) {
    isize_t left = _left(idx);
    isize_t right = _right(idx);
    isize_t smallest = idx;
    if (left < heap_size && array[left] < array[smallest]) {
        smallest = left;
    }
    if (right < heap_size && array[right] < array[smallest]) {
        smallest = right;
    }
    if (smallest != idx) {
        auto tmp = array[idx];
        array[idx] = array[smallest];
        array[smallest] = tmp;
        _min_heapify(array, heap_size, smallest);
    }
}

template <typename T>
inline void _build_min_heap(T& array, isize_t heap_size) {
    for (isize_t idx = heap_size / 2 - 1; idx >= 0; idx--) {
        _min_heapify(array, heap_size, idx);
    }
}

template <typename T>
inline isize_t _partition(T& array, isize_t lo, isize_t hi) {
    auto pivot = array[hi];
    isize_t i = lo;
    for (isize_t j = lo; j < hi; j++) {
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

}  // namespace internal

template <typename T>
inline void scramble(T& array, isize_t size, isize_t repeat_count = 1) {
    for (isize_t count = 0; count < repeat_count; count++) {
        for (isize_t idx = 0; idx < size; idx++) {
            isize_t jdx = anvil::math::rand() % size;
            isize_t kdx = anvil::math::rand() % size;
            auto tmp = array[jdx];
            array[jdx] = array[kdx];
            array[kdx] = tmp;
        }
    }
}

template <typename T>
inline void sort(T& array, isize_t size) {
    // quicksort usually performs better than heapsort because
    // heapsort will always swap every element in the array
    // https://stackoverflow.com/questions/2467751/quicksort-vs-heapsort
    quicksort(array, 0, size);
}

//max heap property: A[parent(i)] >= A[i]
//min heap property: A[parent(i)] <= A[i]
template <typename T>
inline void heapsort(T& array, isize_t heap_size) {
    anvil::containers::internal::_build_max_heap(array, heap_size);
    for (isize_t idx = heap_size - 1; idx > 0; idx--) {
        auto tmp = array[0];
        array[0] = array[idx];
        array[idx] = tmp;
        anvil::containers::internal::_max_heapify(array, idx, 0);
    }
}

template <typename T>
inline void quicksort(T& array, isize_t lo, isize_t hi) {
    if (lo < hi) {
        isize_t p = anvil::containers::internal::_partition(array, lo, hi);
        quicksort(array, lo, p - 1);
        quicksort(array, p + 1, hi);
    }
}

template <typename T, typename U>
inline Option<isize_t> search(const T& array, isize_t size, U item) {
    Option<isize_t> result;
    for (isize_t idx = 0; idx < size; idx++) {
        if (array[idx] == item) {
            result.result = Option<isize_t>::Some;
            result.value = idx;
            return result;  // {.value = idx, .result = Option<isize_t>::Some};
        }
    }
    result.result = Option<isize_t>::None;
    return result;  // {.result = Option<isize_t>::None};
}

}  // namespace containers
}  // namespace anvil
