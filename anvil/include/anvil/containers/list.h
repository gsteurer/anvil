#pragma once
#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

// @@@ TODO
// if a list is empty, dereferencing the iterator segfaults;
// the list needs to have a mechanism to iterate to the end, because
// iterating with a for loop only goes to the second to last element before exiting
template <typename T>
struct List {
    struct Node {
        Node* left;
        Node* right;
        T data;
    };
    class Iterator {
       public:
        Iterator() {
            m_node = nullptr;
        }
        ~Iterator() {
        }
        Iterator(Node* node) {
            m_node = node;
        }
        Iterator(const Iterator& it) {
            m_node = it.m_node;
        }
        Iterator& operator=(const Iterator& it) {
            this->m_node = it.m_node;
            return *this;
        }
        Iterator& operator++() {
            m_node = m_node->right;
            return *this;
        }
        Iterator operator++(int) {
            Iterator it = *this;
            ++*this;
            return it;
        }
        Iterator& operator--() {
            m_node = m_node->left;
            return *this;
        }
        Iterator operator--(int) {
            Iterator it = *this;
            --*this;
            return it;
        }
        T operator*() {
            return m_node->data;
        }
        bool operator!=(const Iterator& rhs) {
            return m_node != rhs.m_node;
        }
        bool operator==(const Iterator& rhs) {
            return m_node == rhs.m_node;
        }
        Node* m_node;
    };
    List();
    List(const List<T>& list);
    List<T>& operator=(const List<T>& list);
    // @@@ TODO List(const List<T>& list);
    // https://en.cppreference.com/w/cpp/language/copy_assignment
    // https://en.cppreference.com/w/cpp/language/operators#Assignment_operator
    ~List();
    isize_t Length();
    Iterator Begin() const;
    Iterator End() const;
    Option<isize_t> IndexOf(T item);
    void PushFront(T item);
    void PushBack(T item);
    void InsertAt(T item, isize_t index);
    Option<T> PopFront();
    Option<T> PopBack();

    Option<T> RemoveAt(isize_t index);
    Option<T> Remove(T item);

    void Clear();

    T operator[](isize_t index) const;
    T& operator[](isize_t index);

   private:
    isize_t m_size;
    Node* m_root;
    Node* m_last;
};

template <typename T>
List<T>::List() {
    m_root = nullptr;
    m_last = nullptr;
    m_size = 0;
}

template <typename T>
List<T>::List(const List<T>& list) : List() {
    for (List<isize_t>::Iterator it = list.Begin(); it != list.End(); it++) {
        this->PushBack(*it);
    }
    this->PushBack(*(list.End()));
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& list) {
    this->Clear();
    for (List<isize_t>::Iterator it = list.Begin(); it != list.End(); it++) {
        this->PushBack(*it);
    }
    this->PushBack(*(list.End()));
    return *this;
}

/*
template <typename T>
List<T>::List(const List<T>& list) {
    // @@@ todo
    m_root = nullptr;
    m_last = nullptr;
    m_size = 0;
}
*/

template <typename T>
List<T>::~List() {
    Clear();
}

template <typename T>
isize_t List<T>::Length() {
    return m_size;
}

template <typename T>
typename List<T>::Iterator List<T>::Begin() const {
    return Iterator(m_root);
}
template <typename T>
typename List<T>::Iterator List<T>::End() const {
    return Iterator(m_last);
}

template <typename T>
Option<isize_t> List<T>::IndexOf(T item) {
    Option<isize_t> result;
    result.result = Option<isize_t>::None;
    isize_t current_index = 0;
    Node* node = m_root;
    while (node != nullptr) {
        if (node->data == item) {
            result.result = Option<isize_t>::Some;
            result.value = current_index;
            return result;
        }
        current_index++;
        node = node->right;
    }
    return result;
}

template <typename T>
void List<T>::PushFront(T item) {
    Node* node = new Node();
    node->data = item;
    node->left = nullptr;
    node->right = nullptr;
    m_size++;
    if (m_root != nullptr) {
        Node* current_root = m_root;
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
    Node* node = new Node();
    node->data = item;
    node->left = nullptr;
    node->right = nullptr;
    m_size++;
    if (m_root != nullptr) {
        Node* current_last = m_last;
        current_last->right = node;
        m_last = node;
        m_last->left = current_last;
    } else {
        m_root = node;
        m_last = m_root;
    }
}

template <typename T>
void List<T>::InsertAt(T item, isize_t index) {
    if (m_root != nullptr) {
        Node* node;
        bool go_right = true;
        isize_t counter;
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
            Node* lhs = node->left;
            Node* new_node = new Node();
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
Option<T> List<T>::PopFront() {
    Option<T> result;
    result.result = Option<T>::None;
    if (m_root != nullptr) {
        Node* node = m_root->right;
        if (node != nullptr) {
            node->left = nullptr;
        }
        result.value = m_root->data;
        result.result = Option<T>::Some;
        delete m_root;
        m_root = node;
        m_size--;
        if (m_size == 0) {
            m_last = nullptr;
        }
    }

    return result;
}

template <typename T>
Option<T> List<T>::PopBack() {
    Option<T> result;
    result.result = Option<T>::None;
    if (m_last != nullptr) {
        Node* node = m_last->left;
        if (node != nullptr) {
            node->right = nullptr;
        }
        result.value = m_last->data;
        result.result = Option<T>::Some;
        delete m_last;
        m_last = node;
        m_size--;
        if (m_size == 0) {
            m_root = nullptr;
        }
    }

    return result;
}

template <typename T>
Option<T> List<T>::RemoveAt(isize_t index) {
    Option<T> result;
    result.result = Option<T>::None;
    if (index < 0 || index > m_size - 1) {
        return result;
    }
    Node* node = m_root;
    isize_t current_index = 0;
    while (current_index < index && node != nullptr) {
        node = node->right;
        current_index++;
    }

    if (node == nullptr) {
        return result;
    }

    Node* left = node->left;
    Node* right = node->right;
    if (left != nullptr) {
        left->right = right;
        if (right == nullptr) {
            m_last = left;
        }
    }

    if (right != nullptr) {
        right->left = left;
        if (left == nullptr) {
            m_root = right;
        }
    }

    if (m_size == 1) {
        m_root = nullptr;
        m_last = nullptr;
    }
    result.value = node->data;
    result.result = Option<T>::Some;
    delete node;
    m_size--;

    return result;
}

template <typename T>
Option<T> List<T>::Remove(T item) {
    Option<T> result = this->IndexOf(item);
    if (result.result == Option<T>::Some) {
        result = this->RemoveAt(result.value);
    }
    return result;
}

template <typename T>
void List<T>::Clear() {
    Node* node = m_root;
    while (node != nullptr) {
        Node* next = node->right;
        node->left = nullptr;
        delete node;
        m_size--;
        node = next;
    }
    m_root = nullptr;
    m_last = nullptr;
}

template <typename T>
T List<T>::operator[](isize_t index) const {
    Node* node = m_root;
    isize_t current_idx = 0;
    // @@@ check if index in [0:msize)

    while (current_idx < index && node != nullptr) {
        node = node->right;
        current_idx++;
    }

    // @@@ this can segfault
    return node->data;
}

template <typename T>
T& List<T>::operator[](isize_t index) {
    Node* node = m_root;
    isize_t current_idx = 0;
    // @@@ check if index in [0:msize)

    while (current_idx < index && node != nullptr) {
        node = node->right;
        current_idx++;
    }

    // @@@ this can segfault
    return node->data;
}

}  // namespace containers
}  // namespace anvil