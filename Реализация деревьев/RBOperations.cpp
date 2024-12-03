#include <iostream>
#include "AVL.h"
#include "BST.h"
#include "RB.h"
using namespace std;

//Вставка
void RedBlackTree::insert(int key) {
    RBNode* node = new RBNode(key);
    node->parent = nullptr;
    node->key = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    RBNode* y = nullptr;
    RBNode* x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y == nullptr)
        root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr)
        return;

    insertFix(node);
}

void RedBlackTree::insertFix(RBNode* k) {
    RBNode* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;

            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root)
            break;
    }
    root->color = BLACK;
}


//Поиск
RBNode* RedBlackTree::search(int key) {
    return searchTreeHelper(this->root, key);
}

RBNode* RedBlackTree::searchTreeHelper(RBNode* node, int key) {
    if (node == TNULL || key == node->key)
        return node;

    if (key < node->key)
        return searchTreeHelper(node->left, key);

    return searchTreeHelper(node->right, key);
}

//Вспомогательные функции
void RedBlackTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RBNode* RedBlackTree::minimum(RBNode* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}


//Удаление
void RedBlackTree::deleteNode(int key) {
    deleteNodeHelper(this->root, key);
}

void RedBlackTree::deleteNodeHelper(RBNode* node, int key) {
    RBNode* z = TNULL;
    RBNode* x, * y;

    // Поиск узла с ключом `key`
    while (node != TNULL) {
        if (node->key == key)
            z = node;

        if (node->key <= key)
            node = node->right;
        else
            node = node->left;
    }

    if (z == TNULL) {
        std::cout << "Узел с ключом " << key << " не найден в дереве.\n";
        return;
    }

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;

    if (yOriginalColor == BLACK) {
        deleteFix(x);
    }
}

//Коррекция дерева
void RedBlackTree::deleteFix(RBNode* x) {
    RBNode* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

