#pragma once

struct AVLNode {
	int key;		  // Ключ узла
	AVLNode* left;       // Левый потомок
	AVLNode* right;      // Правый потомок
	int height;       // Высота узла (для АВЛ-дерева)

	AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}

	int getHeight(AVLNode* node);
	int getBalance(AVLNode* node);
	AVLNode* Right(AVLNode* y);
	AVLNode* Left(AVLNode* x);
	AVLNode* AVLinsert(AVLNode* root, int key);
	AVLNode* AVLsearch(AVLNode* root, int key);
	AVLNode* AVLdeleteNode(AVLNode* root, int key);

};
