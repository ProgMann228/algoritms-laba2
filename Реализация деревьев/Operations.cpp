#include <iostream>
#include "AVL.h"
#include "BST.h"
using namespace std;

// Функции для вставки элемента
AVLNode* AVLNode::AVLinsert(AVLNode* root, int key) {
    if (!root)
        return new AVLNode(key); // Создаём новый узел, если дерево пустое

    if (key < root->key)
        root->left = AVLinsert(root->left, key);
    else if (key > root->key)
        root->right = AVLinsert(root->right, key);
    else
        return root; // Дубликаты не вставляем

    // Обновляем высоту текущего узла
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Проверяем баланс узла
    int balance = getBalance(root);

    // Балансировка
    // RR - правый поворот
    if (balance > 1 && key < root->left->key)
        return Right(root);


    // LL - левый поворот
    if (balance < -1 && key > root->right->key)
        return Left(root);

    // LR - сначала левый, затем правый поворот
    if (balance > 1 && key > root->left->key) {
        root->left = Left(root->left);
        return Right(root);
    }

    // RL - сначала правый, затем левый поворот
    if (balance < -1 && key < root->right->key) {
        root->right = Right(root->right);
        return Left(root);
    }

    return root; // Возвращаем корень (возможно, новый после балансировки)
}

BSTNode* BSTNode::BSTinsert(BSTNode* root, int key) {
    if (!root) {
        return new BSTNode(key);
    }

    BSTNode* current = root;
    while (true) {
        if (key < current->key) {
            if (!current->left) {
                current->left = new BSTNode(key);
                break;
            }
            current = current->left;
        }
        else {
            if (!current->right) {
                current->right = new BSTNode(key);
                break;
            }
            current = current->right;
        }
    }

    return root;
}


// Функции для поиска элемента
AVLNode* AVLNode::AVLsearch(AVLNode* root, int key) {
    if (!root || root->key == key)
        return root;

    if (key < root->key)
        return AVLsearch(root->left, key);

    return AVLsearch(root->right, key);
}

BSTNode* BSTNode::BSTsearch(BSTNode* root, int key) {
    if (!root || root->key == key)
        return root;

    if (key < root->key)
        return BSTsearch(root->left, key);

    return BSTsearch(root->right, key);
}


// Функции для удаления элемента
AVLNode* AVLNode::AVLdeleteNode(AVLNode* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = AVLdeleteNode(root->left, key);
    else if (key > root->key)
        root->right = AVLdeleteNode(root->right, key);
    else {
        // Узел найден
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        else {
            // Минимум из правого поддерева
            AVLNode* temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = AVLdeleteNode(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    // Обновляем высоту
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Проверяем баланс
    int balance = getBalance(root);

    // Балансировка
    if (balance > 1 && getBalance(root->left) >= 0)
        return Right(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = Left(root->left);
        return Right(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return Left(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = Right(root->right);
        return Left(root);
    }

    return root;
}

BSTNode* BSTNode::BSTdeleteNode(BSTNode* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = BSTdeleteNode(root->left, key);
    else if (key > root->key)
        root->right = BSTdeleteNode(root->right, key);
    else {
        // Узел найден
        if (!root->left || !root->right) {
            BSTNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        else {
            // Минимум из правого поддерева
            BSTNode* temp = root->right;
            while (temp->left)
                temp = temp->left;

            root->key = temp->key;
            root->right = BSTdeleteNode(root->right, temp->key);
        }
    }

    return root; // Возвращаем корень
}

