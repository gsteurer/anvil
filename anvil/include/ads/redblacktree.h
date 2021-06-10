#pragma once
#include <string>
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
    T* Search(T item);
    RBNode<T>* m_root;
    RBNode<T>* m_sentinel;
};

template <typename T>
T* RBTree<T>::Search(T item) {
    RBNode<T>* node = m_root;
    while (node != m_sentinel) {
        if (node->key == item) {
            return &node->key;
        } else if (node->key < item) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return nullptr;
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
}

template <typename T>
RBTree<T>::RBTree() {
    RBNode<T>* node = new RBNode<T>();
    node->color = BLACK;
    node->parent = node;
    node->left = node;
    node->right = node;

    m_sentinel = node;
    m_root = node;
}

template <typename T>
void rbLeftRotate(RBTree<T>* tree, RBNode<T>* x) {
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
void rbRightRotate(RBTree<T>* tree, RBNode<T>* x) {
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
void rbInsert(RBTree<T>* tree, RBNode<T>* z) {
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
void rbInsertFixup(RBTree<T>* tree, RBNode<T>* z) {
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