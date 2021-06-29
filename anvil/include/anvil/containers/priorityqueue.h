#pragma once
#include "anvil/containers/arrayutils.h"
#include "anvil/containers/slice.h"
#include "anvil/option.h"
#include "anvil/types.h"
// https://en.wikipedia.org/wiki/Binary_heap
// https://en.wikipedia.org/wiki/Heap_(data_structure)
// https://en.wikipedia.org/wiki/Priority_queue

// slice

namespace anvil {
namespace containers {

template <typename M, typename T>
struct QueueType {
    static void build_heap(T& array, isize_t heap_size);
};

struct MaxPriorityQueue {};
struct MinPriorityQueue {};

template <typename T>
struct QueueType<MaxPriorityQueue, T> {
    static void build_heap(T& array, isize_t heap_size) {
        anvil::containers::internal::_build_max_heap(array, heap_size);
    }
};

template <typename T>
struct QueueType<MinPriorityQueue, T> {
    static void build_heap(T& array, isize_t heap_size) {
        anvil::containers::internal::_build_min_heap(array, heap_size);
    }
};

template <typename T>
struct PriorityQueue {
    PriorityQueue();
    ~PriorityQueue();
    void Push(T item);
    Option<T> Pop();
    Option<T> Peek();
    isize_t Length();

   private:
    Slice<T> m_data;
};

template <typename T>
PriorityQueue<T>::PriorityQueue() {
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
}

template <typename T>
void PriorityQueue<T>::Push(T item) {
    m_data.Insert(item);
    QueueType<MaxPriorityQueue, Slice<T>>::build_heap(m_data, m_data.Length());
}

template <typename T>
Option<T> PriorityQueue<T>::Pop() {
    Option<T> result = Peek();
    if (m_data.Length() > 0) {
        isize_t idx = m_data.Length() - 1;
        m_data[0] = m_data[idx];
        m_data.Remove(idx);
        QueueType<MaxPriorityQueue, Slice<T>>::build_heap(m_data, m_data.Length());
    }
    return result;
}

template <typename T>
Option<T> PriorityQueue<T>::Peek() {
    Option<T> result;
    if (m_data.Length() > 0) {
        result.value = m_data[0];
        result.result = Option<T>::Some;
    }
    return result;
}

template <typename T>
isize_t PriorityQueue<T>::Length() {
    return m_data.Length();
}

}  // namespace containers
}  // namespace anvil