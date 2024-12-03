#ifndef HEADER_H 
#define HEADER_H
#include <string>  
#include <vector>  
#include <queue>
using namespace std;

//Для вывода дерева(используем шаблонную функцию)
template <typename Node>
void printInOrder(Node* root) {
    if (root) {
        printInOrder(root->left);
        if (root->key != 0) cout << root->key << " ";
        printInOrder(root->right);
    }
}

// Функция для вывода дерева
template <typename Node>
void printTree(Node* node, const string& indent = "", bool last = true) {
    if (node != nullptr && node->key != 0) {
        // Определяем цвет узла (если доступен)
        string color = "";
        if constexpr (is_same_v<Node, RBNode>) { // Если узел RBNode
            color = (node->color == RED) ? " (R)" : " (B)";
        }

        // Вывод текущего узла с отступом, символами и цветом
        cout << indent << (last ? "└── " : "├── ") << node->key << color << endl;

        // Обновляем отступ: если узел последний, добавляем "    ", иначе "│   "
        string newIndent = indent + (last ? "    " : "│   ");

        // Рекурсивно выводим правое и левое поддерево
        printTree(node->right, newIndent, false);
        printTree(node->left, newIndent, true);
    }
}

//обходы в блубину
// Прямой обход (Pre-order)
template <typename Node>
void preOrder(Node* root) {
    if (root == nullptr || root->key==0) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Симметричный обход (In-order)
template <typename Node>
void inOrder(Node* root) {
    if (root == nullptr || root->key == 0) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

// Обратный обход (Post-order)
template <typename Node>
void postOrder(Node* root) {
    if (root == nullptr || root->key == 0) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->key << " ";
}

//Обход в ширину
template <typename Node>
void bfs(Node* root) {
    if (root == nullptr || root->key == 0) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current->key != 0)
            cout << current->key << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

//случайное значение ключей(для bst)
template <typename Node>
void analyzeTreeHeights(int n, Node*& AVLroot, RedBlackTree& tree, int interval) {
    // Генерация ключей
    vector<int> keys(n);
    for (int i = 1; i <= n; i++) keys[i - 1] = i;

    // Вывод шапки таблицы
    cout << "Number of Keys\tAVL Height\tRB Height\n";

    // Основной цикл вставки и анализа
    for (int i = 0; i < n; i++) {
        // Вставка в AVL-дерево
        AVLroot = AVLroot->AVLinsert(AVLroot, keys[i]);

        // Вставка в красно-черное дерево
        tree.insert(keys[i]);

        // Проверяем только на контрольных точках
        if ((i + 1) % interval == 0) {
            // Получение высоты AVL-дерева
            int avlHeight = AVLroot->getHeight(AVLroot);

            // Получение высоты красно-черного дерева
            int rbHeight = tree.getRBHeight(tree.root, tree.TNULL);

            // Вывод количества ключей и высот деревьев
            cout << (i + 1) << "\t\t" << avlHeight << "\t\t" << rbHeight << "\n";
        }
    }
}

//случайное значение ключей(для bst)
vector<int> analyzeBSTHeights(const vector<int>& numKeys) {
    vector<int> heights;

    for (int n : numKeys) {
        BSTNode* root = nullptr;

        // Вставка случайных ключей в дерево
        for (int i = 0; i < n; ++i) {
            int randomKey = rand();
            root = root->BSTinsert(root, randomKey);
        }

        // Вычисление высоты дерева
        BSTNode node(0);
        int treeHeight = node.height(root);
        heights.push_back(treeHeight);

        // Освобождаем память
        delete root;
    }

    return heights;
}

vector<int> analyzeWorstCaseBSTHeights(const vector<int>& numKeys) {
    vector<int> heights;

    for (int n : numKeys) {
        BSTNode* root = nullptr;

        // Вставка ключей в строго возрастающем порядке
        for (int i = 0; i < n; ++i) {
            root = root->BSTinsert(root, i);
        }

        // Вычисление высоты дерева
        BSTNode node(0);
        int treeHeight = node.height(root);
        heights.push_back(treeHeight);

        // Освобождаем память
        delete root;
    }

    return heights;
}

#endif // FUNCTIONS_H