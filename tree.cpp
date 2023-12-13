#include <iostream>
typedef int item;
typedef struct node {
    struct node * left;
    struct node * right;
    item data;
    node(item val):data(val){}
}node;

typedef struct Tipnode {
    struct TiPnode * left;
    struct Tipnode * right;
    item data;
    struct Tipnode *from;
    struct Tipnode *to;
    Tipnode(item val): data(val) {}
}Tipnode;

typedef struct tree {
    node * head;
    tree(node *root = nullptr): head(root) {}
}tree;

node *TreeSortInsert(node *root, item val) {
    if(!root) return new node(val);
    if(val < root->data) {
        root->left = TreeSortInsert(root->left , val);
    } else {
        root->right = TreeSortInsert(root->right , val);
    }
    return root;
}
tree *TreeCreate() {
    return new tree();
}
