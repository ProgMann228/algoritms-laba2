#pragma once
struct BSTNode {
    int key;          
    BSTNode* left;    
    BSTNode* right;   

    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}

    BSTNode* BSTinsert(BSTNode* root, int key);
    BSTNode* BSTsearch(BSTNode* root, int key);
    BSTNode* BSTdeleteNode(BSTNode* root, int key);
    int getRandomHeight(int n);
    int getWorstHeight(int n);
    int height(BSTNode* root);

};
