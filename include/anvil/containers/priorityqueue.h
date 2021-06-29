#pragma once
#include "anvil/containers/arrayutils.h"
#include "anvil/containers/slice.h"
#include "anvil/option.h"
#include "anvil/types.h"

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

// page 164 for heap increase key, which promotes a node and rebalances the tree
template <typename M, typename T>
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

template <typename M, typename T>
PriorityQueue<M, T>::PriorityQueue() {
}

template <typename M, typename T>
PriorityQueue<M, T>::~PriorityQueue() {
}

template <typename M, typename T>
void PriorityQueue<M, T>::Push(T item) {
    m_data.Insert(item);
    QueueType<M, Slice<T>>::build_heap(m_data, m_data.Length());
}

template <typename M, typename T>
Option<T> PriorityQueue<M, T>::Pop() {
    Option<T> result = Peek();
    if (m_data.Length() > 0) {
        isize_t idx = m_data.Length() - 1;
        m_data[0] = m_data[idx];
        m_data.Remove(idx);
        QueueType<M, Slice<T>>::build_heap(m_data, m_data.Length());
    }
    return result;
}

template <typename M, typename T>
Option<T> PriorityQueue<M, T>::Peek() {
    Option<T> result;
    if (m_data.Length() > 0) {
        result.value = m_data[0];
        result.result = Option<T>::Some;
    }
    return result;
}

template <typename M, typename T>
isize_t PriorityQueue<M, T>::Length() {
    return m_data.Length();
}

}  // namespace containers
}  // namespace anvil