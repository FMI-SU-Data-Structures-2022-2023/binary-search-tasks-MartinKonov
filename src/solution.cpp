#include "solution.h"

bool isContains(Node* node, int key) {
    if (!node) { return false; }
    if (node->key == key) { return true; }
    if (node->key > key) { return isContains(node->left, key); }
    else { return isContains(node->right, key); }

}

bool isContains(const Node* node, int key) {
    if (!node) { return false; }
    if (node->key == key) { return true; }
    if (node->key > key) { return isContains(node->left, key); }
    else { return isContains(node->right, key); }

}

Node* insert(Node* node, int value) {
    if (!node) { return new Node(value); }
    if(node->key > value){
        node->left = insert(node->left, value);
    }
    if (node->key < value) {
        node->right = insert(node->right, value);
    }

    return node;
}
//test
int getHeight(Node* node) {

    if (!node) { return 0; }
    return 1 + std::max(getHeight(node->left), getHeight(node->right));

}

Node* getMax(Node* node) {
    if (!node->right) { return node; }
    return getMax(node->right);
}

Node* getMin(Node* node) {
    if (!node->left) { return node; }
    return getMin(node->left);
}
//test
bool isLeaf(Node* node) {
    if (!node) {
        return false;
    }

    if (node->left == nullptr && node->right == nullptr) {
        return true;
    }
    return false;
}

Node* remove(Node* node, int key) {
    
    if (node == nullptr) {
        return nullptr;
    }
    
    if (isLeaf(node)) {
         delete node;
         return nullptr;
     }

    if (key == node->key) {

        Node* todel;


        if (!node->left) {
            todel = node->right;
            delete node;
            node = nullptr;
        }
        else if (!node->right) {
            todel = node->left;
            delete node;
            node = nullptr;
        }
        else {

            todel = getMin(node->right);
            Node* newnode = new Node(todel->key);
            newnode->left = node->left;
            newnode->right = node->right;
            delete node;
            node = nullptr;
            newnode->right = remove(newnode->right, todel->key);
            return newnode;
        }
        return todel;
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    if (key > node->key) {
        node->right = remove(node->right, key);
    }
    return node;
}

void copyTrees(const Node* toBeCopied, Node* toCopy) {

    if (!toBeCopied) {
        return;
    }

    insert(toCopy, toBeCopied->key);

    copyTrees(toBeCopied->left, toCopy);
    copyTrees(toBeCopied->right, toCopy);
}

void filterDifs(const Node* r, Node* toFilter) {

    if (!toFilter) {
        return;
    }

    if (!isContains(r, toFilter->key)) {

        toFilter = remove(toFilter, toFilter->key);
        filterDifs(r, toFilter);
    }
    else {
        filterDifs(r, toFilter->left);
        filterDifs(r, toFilter->right);
    }
}

void sectionHelp(const Node* l, const Node* r, Node* result) {

    if (!l) {
        return;
    }

    if (isContains(l, l->key) && isContains(r,l->key)) {
        insert(result, l->key);
    }

    sectionHelp(l->left, r, result);
    sectionHelp(l->right, r, result);
}

Node* section(const Node* l, const Node* r) {
    if (isContains(l, l->key) && isContains(r, l->key)) {
        Node* newnode = new Node(l->key);
        sectionHelp(l, r, newnode);
        return newnode;
    }
    else {
        section(l, r);
    }
    return nullptr;

}

bool areSiblings(const Node* node, int key1, int key2) {

    if (!node)
        return false;

    if (node->left && node->right) {
        int left = node->left->key;
        int right = node->right->key;

        if (left == key1 && right == key2) {
            return true;
        }
        else if (left == key2 && right == key1) {
            return true;
        }
    }

    if (node->left)
        if (areSiblings(node->left, key1, key2)) {
            return true;
        }
    if (node->right)
        if (areSiblings(node->right, key1, key2)) {
            return true;
        }

    return false;
}

int level(const Node* node, int key, int lvl) {

    if (!node) {
        return 0;
    }
    if (node->key == key) {
        return lvl;
    }

    int lv = level(node->left, key, lvl + 1);
    if (lv != 0) {
        return lv;
    }
    
    lv = level(node->right, key, lvl + 1);
    return lv;
}

bool areCousins(const Node* node, int key1, int key2) {
    
    if (!isContains(node, key1) && !isContains(node, key2)) {
        return 0;
    }

    if (level(node, key1, 1) == level(node, key2, 1) && !areSiblings(node, key1, key2)) {
        return 1;
    }
    else {
        return 0;
    }

}

int LCA(const Node* l, int key1, int key2) {
    if (l == nullptr) {
        return -1;
    }
    if (!isContains(l, key1) || !isContains(l, key2)) {
        return -1;
    }

    if ((l->key <= key1 && l->key >= key2) || (l->key >= key1 && l->key <= key2)) {
        return l->key;
    }

    if (l->key > key1 && l -> key > key2) {
        return LCA(l->left, key1, key2);
    }
    if (l->key < key1 && l->key < key2) {
        return LCA(l->right, key1, key2);
    }

}

//test
bool isBalanced(Node* node) {

    if (!node) { return true; }

    if (std::abs(getHeight(node->left) - getHeight(node->right) > 1)) {
        return false;
    }

    return isBalanced(node->left) && isBalanced(node->right);
}

void delTree(Node* node) {

    if (!node) {
        return;
    }

    node = remove(node, node->key);
    delTree(node);
}

Node* delGreaterThanX(Node* node, int x) {
    
    if (!node) {
        return nullptr;
    }

    if(node->key == x){
        delTree(node->right);
        node->right = nullptr;
        return node;

    }
    if (node->key > x) {
        delTree(node->right);
        node->right = nullptr;
        return delGreaterThanX(node->left, x);
    }

    if (node->key < x) {
        return delGreaterThanX(node->right, x);
    }

}


