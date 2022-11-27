#ifndef WEEK7_TREE_H
#include<iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int _key) : key(_key), left(nullptr), right(nullptr) {}
};

bool isContains(Node*, int);
Node* insert(Node*, int);
Node* getMax(Node*);
Node* getMin(Node*);
Node* remove(Node*, int);
Node* section(const Node*, const Node*);
bool areCousins(const Node*, int, int);
int LCA(const Node*, int, int);



void copyTrees(const Node*, Node*);
void filterDifs(const Node*, Node*);
int getHeight(Node*);
void delTree(Node*);
Node* delGreaterThanX(Node*, int);
#define WEEK7_TREE_H

#endif //WEEK7_TREE_H
