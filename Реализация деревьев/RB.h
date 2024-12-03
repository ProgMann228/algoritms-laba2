#pragma once
enum Color { RED, BLACK };

struct RBNode {
    int key;                
    Color color;            
    RBNode* left;         
    RBNode* right;     
    RBNode* parent;

    RBNode(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    // Конструктор по умолчанию (будет использоваться для TNULL)
    RBNode() : key(0), color(BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:

    void initializeNULLNode(RBNode* node, RBNode* parent) {
        node->key = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void insertFix(RBNode* k);
    RBNode* searchTreeHelper(RBNode* node, int key);
    void deleteNodeHelper(RBNode* node, int key);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node);
    void deleteFix(RBNode* x);

public:
    RBNode* TNULL;           // Специальный NULL-узел
    RedBlackTree() {
        TNULL = new RBNode;  // Инициализируем TNULL
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;        // Корень изначально указывает на TNULL
    }
    RBNode* root;
    RBNode* search(int key);
    void insert(int key);
    void deleteNode(int key);
    int getRBHeight(RBNode* node, RBNode* TNULL);
};