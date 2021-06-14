#pragma once
#include "option.h"

template <typename T>
struct ListNode {
    ListNode<T>* left;
    ListNode<T>* right;
    T data;
};

template <typename T>
struct List {
    List();
    List(const List<T>& list);
    // https://en.cppreference.com/w/cpp/language/copy_assignment
    // https://en.cppreference.com/w/cpp/language/operators#Assignment_operator
    ~List();
    int Length();
    Option<int> IndexOf(T item);
    void PushFront(T item);
    void PushBack(T item);
    void InsertAt(T item, int index);
    void PopFront(T item);
    void PopBack(T item);

    Option<T> RemoveAt(int index);

    const T operator[](int index) const;
    T& operator[](int index);

   private:
    int m_size;
    ListNode<T>* m_root;
    ListNode<T>* m_recently_accessed;
    ListNode<T>* m_last;
};

template <typename T>
List<T>::List() {
    m_root = nullptr;
    m_last = nullptr;
    m_recently_accessed = nullptr;
    m_size = 0;
}

template <typename T>
List<T>::List(const List<T>& list) {
    m_root = nullptr;
    m_last = nullptr;
    m_recently_accessed = nullptr;
    m_size = 0;
}

template <typename T>
List<T>::~List() {
    ListNode<T>* node = m_root;
    while (node != nullptr) {
        ListNode<T>* next = node->right;
        node->left = nullptr;
        delete node;
        m_size--;
        node = next;
    }
}

template <typename T>
int List<T>::Length() {
    return m_size;
}
template <typename T>
Option<int> List<T>::IndexOf(T item) {
}

template <typename T>
void List<T>::PushFront(T item) {
    ListNode<T>* node = new ListNode<T>();
    node->data = item;
    node->left = nullptr;
    node->right = nullptr;
    m_size++;
    if (m_root != nullptr) {
        ListNode<T>* current_root = m_root;
        current_root->left = node;
        m_root = node;
        m_root->right = current_root;
    } else {
        m_root = node;
        m_last = m_root;
    }
}
template <typename T>
void List<T>::PushBack(T item) {
    ListNode<T>* node = new ListNode<T>();
    node->data = item;
    node->left = nullptr;
    node->right = nullptr;
    m_size++;
    if (m_root != nullptr) {
        ListNode<T>* current_last = m_last;
        current_last->right = node;
        m_last = node;
        m_last->left = current_last;
    } else {
        m_root = node;
        m_last = m_root;
    }
}

template <typename T>
void List<T>::InsertAt(T item, int index) {
    if (m_root != nullptr) {
        ListNode<T>* node;
        bool go_right = true;
        int counter;
        if (index > m_size / 2) {
            node = m_last;
            go_right = false;
            counter = m_size - 1;
        } else {
            node = m_root;
            counter = 0;
        }
        while (counter != index && node != nullptr) {  // @@@ what happens when node == nullptr?
            node = go_right ? node->right : node->left;
            counter += go_right ? 1 : -1;
        }

        if (index >= m_size) {
            node = m_last;
            counter = m_size;
        }

        // if m_root == m_last, the list gets pushed right
        if (node == m_root || counter == 0) {
            PushFront(item);
        } else if (counter >= m_size) {
            PushBack(item);
        } else {
            ListNode<T>* lhs = node->left;
            ListNode<T>* new_node = new ListNode<T>();
            new_node->data = item;
            new_node->left = lhs;
            lhs->right = new_node;
            new_node->right = node;
            node->left = new_node;
            m_size++;
        }
    } else {
        PushFront(item);
    }
}

template <typename T>
void List<T>::PopFront(T item) {
}
template <typename T>
void List<T>::PopBack(T item) {
}
template <typename T>
Option<T> RemoveAt(int index) {
}

template <typename T>
const T List<T>::operator[](int index) const {
    ListNode<T>* node = m_root;
    int current_idx = 0;
    // @@@ check if index in [0:msize)

    while (current_idx < index && node != nullptr) {
        node = node->right;
        current_idx++;
    }
    // @@@ this can segfault
    return node->data;
}

template <typename T>
T& List<T>::operator[](int index) {
    ListNode<T>* node = m_root;
    int current_idx = 0;
    // @@@ check if index in [0:msize)
    while (current_idx < index && node != nullptr) {
        node = node->right;
        current_idx++;
    }
    // @@@ this can segfault
    return node->data;
}
