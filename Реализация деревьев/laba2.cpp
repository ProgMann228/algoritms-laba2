#include <iostream>
#include <iomanip> 
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include "AVL.h"
#include "BST.h"
#include "RB.h"
#include "Header.h"
using namespace std;

int AVLNode::getHeight(AVLNode* node) {
    if (node) return node->height;
    else return 0;
}

int AVLNode::getBalance(AVLNode* node) {
    if (node) return getHeight(node->left) - getHeight(node->right);
    else return 0;
}

int BSTNode::height(BSTNode* root) {
    if (!root) return 0;

    queue<BSTNode*> q;
    q.push(root);
    int height = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            BSTNode* current = q.front();
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        ++height;
    }

    return height;
}

int RedBlackTree::getRBHeight(RBNode* node, RBNode* TNULL) {
    if (node == TNULL) return 0;
    return 1 + max(getRBHeight(node->left, TNULL), getRBHeight(node->right, TNULL));
}

//ПОВОРОТЫ

AVLNode* AVLNode::Right(AVLNode* y) {    //ПРАВЫЙ
    AVLNode* x = y->left;
    AVLNode* T = x->right;

    x->right = y;
    y->left = T;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVLNode::Left(AVLNode* x) { //ЛЕВЫЙ
    AVLNode* y = x->right;
    AVLNode* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

void RedBlackTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != TNULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;

    if (x->right != TNULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}


int main()
{
    setlocale(LC_ALL, "");

    AVLNode* AVLroot = nullptr;
    BSTNode* BSTroot = nullptr;
    RedBlackTree tree;

    // Вставляем элементы в дерево
    AVLroot = AVLroot->AVLinsert(AVLroot, 8);
    AVLroot = AVLroot->AVLinsert(AVLroot, 10);
    AVLroot = AVLroot->AVLinsert(AVLroot, 18);
    AVLroot = AVLroot->AVLinsert(AVLroot, 19);
    AVLroot = AVLroot->AVLinsert(AVLroot, 20);
    AVLroot = AVLroot->AVLinsert(AVLroot, 30);

    // Массив элементов для вставки
    vector<int> keys = { 8, 18, 10, 19, 20, 30 };

    // Генерация случайного числа на основе времени
    srand(static_cast<unsigned>(time(0)));

    // Перемешиваем элементы массива случайным образом
    random_device rd;
    mt19937 g(rd());
    shuffle(keys.begin(), keys.end(), g);

    // Вставляем элементы в дерево в случайном порядке
    for (int key : keys) {
        BSTroot = BSTroot->BSTinsert(BSTroot, key);
    }
    
    tree.insert(8);
    tree.insert(10);
    tree.insert(18);
    tree.insert(19);
    tree.insert(20);
    tree.insert(30);

    // Выводим дерево (обход в глубину и ширину)
    
    cout << '\n';
    printTree(AVLroot);
    cout << '\n'<<"Обходы в глубину:";
    cout << "\nПрямой ";
    preOrder(AVLroot);
    cout << "\nСимметричный: ";
    inOrder(AVLroot);
    cout << "\nОбратный: ";
    postOrder(AVLroot);
    cout << "\nОбход в ширину:\n";
    bfs(AVLroot);
    
    cout << "\n\n";
    printTree(BSTroot);
    cout << '\n' << "Обходы:";
    cout << "\nПрямой: ";
    preOrder(BSTroot);
    cout << "\nСимметричный: ";
    inOrder(BSTroot);
    cout << "\nОбратный: ";
    postOrder(BSTroot);
    cout << "\nОбход в ширину:\n";
    bfs(BSTroot);


    cout << "\n\n";
    printTree(tree.root);
    cout << '\n' << "Обходы:";
    cout << "\nПрямой: ";
    preOrder(tree.root);
    cout << "\nСимметричный: ";
    inOrder(tree.root);
    cout << "\nОбратный: ";
    postOrder(tree.root);
    cout << "\nОбход в ширину:\n";
    bfs(tree.root);
   

    //получения зависимости для bst
    /*srand(static_cast<unsigned>(time(nullptr)));

    vector<int> numKeys;
    for (int i = 0, n = 100; i < 100; i++, n += 100) numKeys.push_back(n);

    //лучший и средний случат
    vector<int> heights = analyzeBSTHeights(numKeys);

    // Выводим результаты
    cout << "Количество ключей | Высота дерева" << endl;
    for (size_t i = 0; i < numKeys.size(); ++i) {
        cout << numKeys[i] << " | " << heights[i] << endl;
    }

    // Анализ худшего случая
    vector<int> worstCaseHeights = analyzeWorstCaseBSTHeights(numKeys);

    // Выводим результаты
    cout << "\nХудший случай (вырожденный BST):" << endl;
    cout << "Количество ключей | Высота дерева" << endl;
    for (size_t i = 0; i < numKeys.size(); ++i) {
        cout << numKeys[i] << " | " << worstCaseHeights[i] << endl;
    }*/
    

    //получения зависимости для авл и rb
    int n = 10000; // Количество ключей
   // analyzeTreeHeights(n, AVLroot, tree, 100);
}

