#pragma once
#include <string>

#include "option.h"

enum Color { NONE = 0,
             BLACK = 1,
             RED = 2 };

std::string str(Color c) {
    switch (c) {
        case BLACK:
            return std::string("BLACK");
            break;
        case RED:
            return std::string("RED");
            break;
        default:
            return std::string("NONE");
            break;
    }
}

template <typename T>
struct RBNode {
    Color color;
    RBNode<T>* parent;
    RBNode<T>* left;
    RBNode<T>* right;
    T key;
};

template <typename T>
struct RBTree {
    RBTree();
    void Insert(T item);
    void Delete(T item);
    Option<T> Search(T item);
    int Height(RBNode<T>* node = nullptr);
    T Min();
    T Max();
    int Size() const;
    RBNode<T>* m_root;
    RBNode<T>* m_sentinel;
    int m_size;
};

template <typename T>
RBTree<T>::RBTree() {
    RBNode<T>* node = new RBNode<T>();
    node->color = BLACK;
    node->parent = node;
    node->left = node;
    node->right = node;

    m_sentinel = node;
    m_root = node;
    m_size = 0;
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
int RBTree<T>::Height(RBNode<T>* node) {
    if (node == nullptr) {
        node = m_root;
    }
    if (m_root == m_sentinel) {
        return 0;
    }
    int l = 0;
    int r = 0;
    if (node->left != m_sentinel) {
        l = Height(node->left);
    }
    if (node->right != m_sentinel) {
        r = Height(node->right);
    }
    return (l > r ? l : r) + 1;
}

template <typename T>
int RBTree<T>::Size() const {
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
    node->color = RED;
    node->parent = m_sentinel;
    node->left = m_sentinel;
    node->right = m_sentinel;
    node->key = item;
    if (m_root != m_sentinel) {
        rbInsert(this, node);
    } else {
        node->color = BLACK;
        m_root = node;
    }
    m_size++;
}

template <typename T>
void RBTree<T>::Delete(T item) {
    RBNode<T>* node = rbSearch(this, item);
    if (node != nullptr) {
        rbDelete(this, node);
        m_size--;
    }
}

template <typename T>
inline RBNode<T>* rbTreeMinimum(RBNode<T>* node, RBNode<T>* sentinel) {
    RBNode<T>* last_node;
    while (node != sentinel) {
        last_node = node;
        node = node->left;
    }
    return last_node;
}

template <typename T>
inline RBNode<T>* rbTreeMaximum(RBNode<T>* node, RBNode<T>* sentinel) {
    RBNode<T>* last_node;
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
    z->color = RED;
    rbInsertFixup(tree, z);
}

template <typename T>
inline void rbInsertFixup(RBTree<T>* tree, RBNode<T>* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode<T>* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbLeftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbRightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode<T>* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbRightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbLeftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->m_root->color = BLACK;
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
    while (x != tree->m_root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode<T>* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbLeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbRightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbLeftRotate(tree, x->parent);
                x = tree->m_root;
            }
        } else {
            RBNode<T>* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbRightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbLeftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbRightRotate(tree, x->parent);
                x = tree->m_root;
            }
        }
    }
    x->color = BLACK;
}

template <typename T>
inline void rbDelete(RBTree<T>* tree, RBNode<T>* z) {
    RBNode<T>* y = z;
    RBNode<T>* x;
    Color y_original_color = y->color;
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

    if (y_original_color == BLACK) {
        rbDeleteFixup(tree, x);
    }
}