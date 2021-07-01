#pragma once
#include <string>

#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

template <typename T>
struct RBTree {
    struct Node {
        enum Color { NONE = 0,
                     BLACK = 1,
                     RED = 2 };
        Color color;
        Node* parent;
        Node* left;
        Node* right;
        T key;
    };
    RBTree();
    ~RBTree();
    void Insert(T item);
    Option<T> Delete(T item);
    void Clear();
    Option<T> Search(T item) const;
    isize_t Height() const;
    Option<T> Min() const;
    Option<T> Max() const;
    isize_t Size() const;
    Node* m_root;
    Node* m_sentinel;
    isize_t m_size;
};

template <typename T>
RBTree<T>::RBTree() {
    Node* node = new Node();
    node->color = Node::BLACK;
    node->parent = node;
    node->left = node;
    node->right = node;

    m_sentinel = node;
    m_root = node;
    m_size = 0;
}

namespace internal {

template <typename T>
inline typename RBTree<T>::Node* rbTreeMinimum(typename RBTree<T>::Node* node, typename RBTree<T>::Node* sentinel) {
    typename RBTree<T>::Node* last_node = node;
    while (node != sentinel) {
        last_node = node;
        node = node->left;
    }
    return last_node;
}

template <typename T>
inline typename RBTree<T>::Node* rbTreeMaximum(typename RBTree<T>::Node* node, typename RBTree<T>::Node* sentinel) {
    typename RBTree<T>::Node* last_node = node;
    while (node != sentinel) {
        last_node = node;
        node = node->right;
    }
    return last_node;
}

template <typename T>
inline typename RBTree<T>::Node* rbSearch(const RBTree<T>* tree, T item) {
    typename RBTree<T>::Node* node = tree->m_root;
    while (node != tree->m_sentinel) {
        if (node->key == item) {
            if (node->left->key == item && node->left != tree->m_sentinel) {
                node = node->left;
            } else if (node->right->key == item && node->right != tree->m_sentinel) {
                node = node->right;
            } else {
                return node;
            }
        } else if (node->key < item) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return nullptr;
}

template <typename T>
isize_t rbHeight(typename RBTree<T>::Node* node, typename RBTree<T>::Node* sentinel) {
    isize_t l = 0;
    isize_t r = 0;
    if (node->left != sentinel) {
        l = rbHeight<T>(node->left, sentinel);
    }
    if (node->right != sentinel) {
        r = rbHeight<T>(node->right, sentinel);
    }
    return (l > r ? l : r) + 1;
}

template <typename T>
inline void rbLeftRotate(RBTree<T>* tree, typename RBTree<T>::Node* x) {
    typename RBTree<T>::Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->m_sentinel) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->m_sentinel) {
        tree->m_root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename T>
inline void rbRightRotate(RBTree<T>* tree, typename RBTree<T>::Node* x) {
    typename RBTree<T>::Node* y = x->left;
    x->left = y->right;
    if (y->right != tree->m_sentinel) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->m_sentinel) {
        tree->m_root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template <typename T>
inline void rbInsertFixup(RBTree<T>* tree, typename RBTree<T>::Node* z) {
    while (z->parent->color == RBTree<T>::Node::RED) {
        if (z->parent == z->parent->parent->left) {
            typename RBTree<T>::Node* y = z->parent->parent->right;
            if (y->color == RBTree<T>::Node::RED) {
                z->parent->color = RBTree<T>::Node::BLACK;
                y->color = RBTree<T>::Node::BLACK;
                z->parent->parent->color = RBTree<T>::Node::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbLeftRotate(tree, z);
                }
                z->parent->color = RBTree<T>::Node::BLACK;
                z->parent->parent->color = RBTree<T>::Node::RED;
                rbRightRotate(tree, z->parent->parent);
            }
        } else {
            typename RBTree<T>::Node* y = z->parent->parent->left;
            if (y->color == RBTree<T>::Node::RED) {
                z->parent->color = RBTree<T>::Node::BLACK;
                y->color = RBTree<T>::Node::BLACK;
                z->parent->parent->color = RBTree<T>::Node::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbRightRotate(tree, z);
                }
                z->parent->color = RBTree<T>::Node::BLACK;
                z->parent->parent->color = RBTree<T>::Node::RED;
                rbLeftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->m_root->color = RBTree<T>::Node::BLACK;
}

template <typename T>
inline void rbTransplant(RBTree<T>* tree, typename RBTree<T>::Node* u, typename RBTree<T>::Node* v) {
    if (u->parent == tree->m_sentinel) {
        tree->m_root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template <typename T>
inline void rbInsert(RBTree<T>* tree, typename RBTree<T>::Node* z) {
    typename RBTree<T>::Node* y = tree->m_sentinel;
    typename RBTree<T>::Node* x = tree->m_root;
    while (x != tree->m_sentinel) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == tree->m_sentinel) {
        tree->m_root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = tree->m_sentinel;
    z->right = tree->m_sentinel;
    z->color = RBTree<T>::Node::RED;
    rbInsertFixup(tree, z);
}

template <typename T>
inline void rbDeleteFixup(RBTree<T>* tree, typename RBTree<T>::Node* x) {
    while (x != tree->m_root && x->color == RBTree<T>::Node::BLACK) {
        if (x == x->parent->left) {
            typename RBTree<T>::Node* w = x->parent->right;
            if (w->color == RBTree<T>::Node::RED) {
                w->color = RBTree<T>::Node::BLACK;
                x->parent->color = RBTree<T>::Node::RED;
                rbLeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTree<T>::Node::BLACK && w->right->color == RBTree<T>::Node::BLACK) {
                w->color = RBTree<T>::Node::RED;
                x = x->parent;
            } else {
                if (w->right->color == RBTree<T>::Node::BLACK) {
                    w->left->color = RBTree<T>::Node::BLACK;
                    w->color = RBTree<T>::Node::RED;
                    rbRightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RBTree<T>::Node::BLACK;
                w->right->color = RBTree<T>::Node::BLACK;
                rbLeftRotate(tree, x->parent);
                x = tree->m_root;
            }
        } else {
            typename RBTree<T>::Node* w = x->parent->left;
            if (w->color == RBTree<T>::Node::RED) {
                w->color = RBTree<T>::Node::BLACK;
                x->parent->color = RBTree<T>::Node::RED;
                rbRightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == RBTree<T>::Node::BLACK && w->right->color == RBTree<T>::Node::BLACK) {
                w->color = RBTree<T>::Node::RED;
                x = x->parent;
            } else {
                if (w->left->color == RBTree<T>::Node::BLACK) {
                    w->right->color = RBTree<T>::Node::BLACK;
                    w->color = RBTree<T>::Node::RED;
                    rbLeftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RBTree<T>::Node::BLACK;
                w->left->color = RBTree<T>::Node::BLACK;
                rbRightRotate(tree, x->parent);
                x = tree->m_root;
            }
        }
    }
    x->color = RBTree<T>::Node::BLACK;
}

template <typename T>
inline void rbDelete(RBTree<T>* tree, typename RBTree<T>::Node* z) {
    typename RBTree<T>::Node* y = z;
    typename RBTree<T>::Node* x;
    typename RBTree<T>::Node::Color y_original_color = y->color;
    if (z->left == tree->m_sentinel) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->m_sentinel) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = rbTreeMinimum<T>(z->right, tree->m_sentinel);
        y_original_color = y->color;
        x = y->right;
        if (x->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == RBTree<T>::Node::BLACK) {
        rbDeleteFixup(tree, x);
    }
}

template <typename T>
::std::string str(typename RBTree<T>::Node::Color c) {
    switch (c) {
        case RBTree<T>::Node::BLACK:
            return ::std::string("BLACK");
            break;
        case RBTree<T>::Node::RED:
            return ::std::string("RED");
            break;
        default:
            return ::std::string("NONE");
            break;
    }
}

}  // namespace internal

template <typename T>
RBTree<T>::~RBTree() {
    this->Clear();
    delete m_sentinel;

    // the following delete implementation leaked memory and i dont know why
    // the first time I noticed it: insert 100000 (9158 was the first quantity I discoveRBTree<T>::Node::RED) random numbers isize_to the tree
    // iterating over a list of each element and calling delete directly does not leak
    // then MSVC++ caught uninitialized values tripping up search, so they were initialized.
    // next, adding a duplicate test revelead nodes with identical keys were getting leaked.
    /*
    while (m_root != m_sentinel) {
        typename RBTree<T>::Node* node = rbSearch(this, rbTreeMinimum(this->m_root, this->m_sentinel)->key);
        rbDelete(this, node);
        delete node;
    }
    delete m_sentinel;
    */
}

template <typename T>
void RBTree<T>::Clear() {
    Node* node = internal::rbTreeMinimum<T>(this->m_root, this->m_sentinel);
    while (m_root != m_sentinel) {
        internal::rbDelete(this, node);
        m_size--;
        delete node;
        node = internal::rbTreeMinimum<T>(this->m_root, this->m_sentinel);
    }
}

template <typename T>
Option<T> RBTree<T>::Min() const {
    Option<T> result;
    Node* node = internal::rbTreeMinimum<T>(this->m_root, this->m_sentinel);
    if (node != nullptr && node != m_sentinel) {
        result.result = Option<T>::Some;
        result.value = node->key;
    }

    result.result = Option<T>::None;
    return result;
}

template <typename T>
Option<T> RBTree<T>::Max() const {
    Option<T> result;
    Node* node = internal::rbTreeMaximum<T>(this->m_root, this->m_sentinel);
    if (node != nullptr && node != m_sentinel) {
        result.result = Option<T>::Some;
        result.value = node->key;
    }

    result.result = Option<T>::None;
    return result;
}

template <typename T>
isize_t RBTree<T>::Height() const {
    if (m_root == m_sentinel || m_root == nullptr) {
        return 0;
    }
    return internal::rbHeight<T>(m_root, m_sentinel);
}

template <typename T>
isize_t RBTree<T>::Size() const {
    return m_size;
}

template <typename T>
Option<T> RBTree<T>::Search(T item) const {
    Node* node = internal::rbSearch(this, item);
    Option<T> result;
    if (node != nullptr && node != m_sentinel) {
        result.result = Option<T>::Some;
        result.value = node->key;
        return result;  // @@@ {.result = Option<T>::Some, .value = node->key};
    }
    result.result = Option<T>::None;
    return result;  // @@@ {.result = Option<T>::None};
}

template <typename T>
void RBTree<T>::Insert(T item) {
    Node* node = new Node();
    node->color = Node::RED;
    node->parent = m_sentinel;
    node->left = m_sentinel;
    node->right = m_sentinel;
    node->key = item;
    if (m_root != m_sentinel) {
        internal::rbInsert(this, node);
    } else {
        node->color = Node::BLACK;
        m_root = node;
    }
    m_size++;
}

template <typename T>
Option<T> RBTree<T>::Delete(T item) {
    Option<T> result;
    Node* node = internal::rbSearch(this, item);
    if (node != nullptr) {
        result.result = Option<T>::Some;
        result.value = node->key;
        internal::rbDelete(this, node);
        delete node;
        m_size--;
    }

    return result;
}

}  // namespace containers
}  // namespace anvil