#pragma once
#include <cstdlib>

#include "option.h"

template <typename T>
void scramble(T& array, int size, int repeat_count = 1) {
    for (int count = 0; count < repeat_count; count++) {
        for (int idx = 0; idx < size; idx++) {
            int jdx = std::rand() % size;
            int kdx = std::rand() % size;
            auto tmp = array[jdx];
            array[jdx] = array[kdx];
            array[kdx] = tmp;
        }
    }
}

template <typename T>
void sort(T& array, int size) {
    // quicksort usually performs better than heapsort because
    // heapsort will always swap every element in the array
    // https://stackoverflow.com/questions/2467751/quicksort-vs-heapsort
    quicksort(array, 0, size);
}

//max heap property: A[parent(i)] >= A[i]
//min heap property: A[parent(i)] <= A[i]
template <typename T>
void heapsort(T& array, int heap_size) {
    _build_max_heap(array, heap_size);
    for (int idx = heap_size - 1; idx > 0; idx--) {
        auto tmp = array[0];
        array[0] = array[idx];
        array[idx] = tmp;
        _max_heapify(array, idx, 0);
    }
}

inline int _parent(int idx) { return idx / 2; }
inline int _left(int idx) { return 2 * idx + 1; }
inline int _right(int idx) { return 2 * idx + 2; }

template <typename T>
void _max_heapify(T& array, int heap_size, int idx) {
    int left = _left(idx);
    int right = _right(idx);
    int largest = idx;
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
void _build_max_heap(T& array, int heap_size) {
    for (int idx = heap_size / 2 - 1; idx >= 0; idx--) {
        _max_heapify(array, heap_size, idx);
    }
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
Option<int> search(T& array, int size, U item) {
    Option<int> result;
    for (int idx = 0; idx < size; idx++) {
        if (array[idx] == item) {
            result.result = Option<int>::Some;
            result.value = idx;
            return result;  // {.value = idx, .result = Option<int>::Some};
        }
    }
    result.result = Option<int>::None;
    return result;  // {.result = Option<int>::None};
}