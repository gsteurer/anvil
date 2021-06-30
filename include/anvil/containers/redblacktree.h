#pragma once
#include <string>

#include "anvil/option.h"
#include "anvil/types.h"

namespace anvil {
namespace containers {

template <typename T>
struct RBNode {
    enum Color { NONE = 0,
                 BLACK = 1,
                 RED = 2 };
    Color color;
    RBNode<T>* parent;
    RBNode<T>* left;
    RBNode<T>* right;
    T key;
};

template <typename T>
std::string str(typename RBNode<T>::Color c) {
    switch (c) {
        case RBNode<T>::BLACK:
            return std::string("BLACK");
            break;
        case RBNode<T>::RED:
            return std::string("RED");
            break;
        default:
            return std::string("NONE");
            break;
    }
}

template <typename T>
struct RBTree {
    RBTree();
    ~RBTree();
    void Insert(T item);
    void Delete(T item);
    void Clear();
    Option<T> Search(T item);
    isize_t Height(RBNode<T>* node = nullptr);
    T Min();
    T Max();
    isize_t Size() const;
    RBNode<T>* m_root;
    RBNode<T>* m_sentinel;
    isize_t m_size;
};

template <typename T>
RBTree<T>::RBTree() {
    RBNode<T>* node = new RBNode<T>();
    node->color = RBNode<T>::BLACK;
    node->parent = node;
    node->left = node;
    node->right = node;

    m_sentinel = node;
    m_root = node;
    m_size = 0;
}

template <typename T>
RBTree<T>::~RBTree() {
    this->Clear();
    delete m_sentinel;

    // the following delete implementation leaked memory and i dont know why
    // insert 100000 (9158 was the first quantity I discoveRBNode<T>::RED) random numbers isize_to the tree
    // iterating over a list of each element and calling delete directly does not leak
    // @@@ TODO check if rbMin/rbMax function we're fucking up because last_node wasn't initialized before being used in a while loop
    // AND MSVC++ WAS THE ONE THAT CAUGHT IT, CLANG COULD NOT BE BOTHERBNode<T>::RED EVEN WITH -wall -wextra
    /*
    while (m_root != m_sentinel) {
        RBNode<T>* node = rbSearch(this, rbTreeMinimum(this->m_root, this->m_sentinel)->key);
        rbDelete(this, node);
        delete node;
    }
    delete m_sentinel;
    */
}

template <typename T>
void RBTree<T>::Clear() {
    RBNode<T>* node = rbTreeMinimum(this->m_root, this->m_sentinel);
    while (m_root != m_sentinel) {
        rbDelete(this, node);
        m_size--;
        delete node;
        node = rbTreeMinimum(this->m_root, this->m_sentinel);
    }
}

template <typename T>
T RBTree<T>::Min() {
    return rbTreeMinimum(this->m_root, this->m_sentinel)->key;
}

template <typename T>
T RBTree<T>::Max() {
    return rbTreeMaximum(this->m_root, this->m_sentinel)->key;
}

template <typename T>
isize_t RBTree<T>::Height(RBNode<T>* node) {
    if (node == nullptr) {
        node = m_root;
    }
    if (m_root == m_sentinel) {
        return 0;
    }
    isize_t l = 0;
    isize_t r = 0;
    if (node->left != m_sentinel) {
        l = Height(node->left);
    }
    if (node->right != m_sentinel) {
        r = Height(node->right);
    }
    return (l > r ? l : r) + 1;
}

template <typename T>
isize_t RBTree<T>::Size() const {
    return m_size;
}

template <typename T>
Option<T> RBTree<T>::Search(T item) {
    RBNode<T>* node = rbSearch(this, item);
    Option<T> result;
    if (node != nullptr) {
        result.result = Option<T>::Some;
        result.value = node->key;
        return result;  // {.result = Option<T>::Some, .value = node->key};
    }
    result.result = Option<T>::None;
    return result;  // {.result = Option<T>::None};
}

template <typename T>
void RBTree<T>::Insert(T item) {
    RBNode<T>* node = new RBNode<T>();
    node->color = RBNode<T>::RED;
    node->parent = m_sentinel;
    node->left = m_sentinel;
    node->right = m_sentinel;
    node->key = item;
    if (m_root != m_sentinel) {
        rbInsert(this, node);
    } else {
        node->color = RBNode<T>::BLACK;
        m_root = node;
    }
    m_size++;
}

template <typename T>
void RBTree<T>::Delete(T item) {
    RBNode<T>* node = rbSearch(this, item);
    if (node != nullptr) {
        rbDelete(this, node);
        delete node;
        m_size--;
    }
}

template <typename T>
inline RBNode<T>* rbTreeMinimum(RBNode<T>* node, RBNode<T>* sentinel) {
    RBNode<T>* last_node = node;
    while (node != sentinel) {
        last_node = node;
        node = node->left;
    }
    return last_node;
}

template <typename T>
inline RBNode<T>* rbTreeMaximum(RBNode<T>* node, RBNode<T>* sentinel) {
    RBNode<T>* last_node = node;
    while (node != sentinel) {
        last_node = node;
        node = node->right;
    }
    return last_node;
}

template <typename T>
inline RBNode<T>* rbSearch(RBTree<T>* tree, T item) {
    RBNode<T>* node = tree->m_root;
    while (node != tree->m_sentinel) {
        if (node->key == item) {
            return node;
        } else if (node->key < item) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return nullptr;
}

template <typename T>
inline void rbLeftRotate(RBTree<T>* tree, RBNode<T>* x) {
    RBNode<T>* y = x->right;
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
inline void rbRightRotate(RBTree<T>* tree, RBNode<T>* x) {
    RBNode<T>* y = x->left;
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
inline void rbInsert(RBTree<T>* tree, RBNode<T>* z) {
    RBNode<T>* y = tree->m_sentinel;
    RBNode<T>* x = tree->m_root;
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
    z->color = RBNode<T>::RED;
    rbInsertFixup(tree, z);
}

template <typename T>
inline void rbInsertFixup(RBTree<T>* tree, RBNode<T>* z) {
    while (z->parent->color == RBNode<T>::RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode<T>* y = z->parent->parent->right;
            if (y->color == RBNode<T>::RED) {
                z->parent->color = RBNode<T>::BLACK;
                y->color = RBNode<T>::BLACK;
                z->parent->parent->color = RBNode<T>::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbLeftRotate(tree, z);
                }
                z->parent->color = RBNode<T>::BLACK;
                z->parent->parent->color = RBNode<T>::RED;
                rbRightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode<T>* y = z->parent->parent->left;
            if (y->color == RBNode<T>::RED) {
                z->parent->color = RBNode<T>::BLACK;
                y->color = RBNode<T>::BLACK;
                z->parent->parent->color = RBNode<T>::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbRightRotate(tree, z);
                }
                z->parent->color = RBNode<T>::BLACK;
                z->parent->parent->color = RBNode<T>::RED;
                rbLeftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->m_root->color = RBNode<T>::BLACK;
}

template <typename T>
inline void rbTransplant(RBTree<T>* tree, RBNode<T>* u, RBNode<T>* v) {
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
inline void rbDeleteFixup(RBTree<T>* tree, RBNode<T>* x) {
    while (x != tree->m_root && x->color == RBNode<T>::BLACK) {
        if (x == x->parent->left) {
            RBNode<T>* w = x->parent->right;
            if (w->color == RBNode<T>::RED) {
                w->color = RBNode<T>::BLACK;
                x->parent->color = RBNode<T>::RED;
                rbLeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBNode<T>::BLACK && w->right->color == RBNode<T>::BLACK) {
                w->color = RBNode<T>::RED;
                x = x->parent;
            } else {
                if (w->right->color == RBNode<T>::BLACK) {
                    w->left->color = RBNode<T>::BLACK;
                    w->color = RBNode<T>::RED;
                    rbRightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RBNode<T>::BLACK;
                w->right->color = RBNode<T>::BLACK;
                rbLeftRotate(tree, x->parent);
                x = tree->m_root;
            }
        } else {
            RBNode<T>* w = x->parent->left;
            if (w->color == RBNode<T>::RED) {
                w->color = RBNode<T>::BLACK;
                x->parent->color = RBNode<T>::RED;
                rbRightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == RBNode<T>::BLACK && w->right->color == RBNode<T>::BLACK) {
                w->color = RBNode<T>::RED;
                x = x->parent;
            } else {
                if (w->left->color == RBNode<T>::BLACK) {
                    w->right->color = RBNode<T>::BLACK;
                    w->color = RBNode<T>::RED;
                    rbLeftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RBNode<T>::BLACK;
                w->left->color = RBNode<T>::BLACK;
                rbRightRotate(tree, x->parent);
                x = tree->m_root;
            }
        }
    }
    x->color = RBNode<T>::BLACK;
}

template <typename T>
inline void rbDelete(RBTree<T>* tree, RBNode<T>* z) {
    RBNode<T>* y = z;
    RBNode<T>* x;
    typename RBNode<T>::Color y_original_color = y->color;
    if (z->left == tree->m_sentinel) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->m_sentinel) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = rbTreeMinimum(z->right, tree->m_sentinel);
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

    if (y_original_color == RBNode<T>::BLACK) {
        rbDeleteFixup(tree, x);
    }
}

}  // namespace containers
}  // namespace anvil