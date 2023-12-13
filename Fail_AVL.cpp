// fail code , 使用非递归的想法，但是每次进行spin后，GetFuther会错误，再进行修改比较麻烦
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std ; 
typedef struct AVLNode {
    int data ; 
    struct AVLNode *left ; 
    struct AVLNode *right ; 
    struct AVLNode *parent ; 
    int BF ; 
    int depth ; 
    AVLNode(int data, struct AVLNode *parent = nullptr) :data(data), parent(parent) {
        left = nullptr ; 
        right = nullptr ; 
        BF = 0 ; 
        depth = 1 ; 
    }
}AVLNode ; 
AVLNode *GetFuther(AVLNode *node) {
    if(!node) return nullptr ; 
    return node->parent ; 
}
int GetBF(AVLNode *node) {
    if(!node) return 0 ; 
    return node->BF ; 
}
int GetDeepth(AVLNode *node) {
    if(!node) return 0 ; 
    return node->depth ; 
}
AVLNode *LeftSpin(AVLNode *node) {
    AVLNode *result = node->right ; 
    result->left = node ; 
    return result ; 
}
AVLNode *RightSpin(AVLNode *node) {
    AVLNode *result = node->left ; 
    result->right = node ; 
    node->left = nullptr ; 
    return result ; 
}
AVLNode *LeftRightSpin(AVLNode *node) {
    AVLNode *result ; 
    node->left = LeftSpin(node->left) ; 
    result = RightSpin(node) ; 
    return result ; 
}
AVLNode *RightLeftSpin(AVLNode *node) {
    AVLNode *result ; 
    node->right = RightSpin(node->right) ; 
    result = LeftSpin(node) ; 
    return result ; 
}
void Spin1(AVLNode *node) {
    if(node->BF == -2 && node->left->BF == -1) node->parent->left = RightSpin(node) ; 
    else if(node->BF == -2 && node->left->BF == 1) node->parent->left = LeftRightSpin(node) ; 
    else if(node->BF == 2 && node->right->BF == -1) node->parent->left = RightLeftSpin(node) ; 
    else node->parent->left = LeftSpin(node) ; 
}
void Spin2(AVLNode *node) {
    if(node->BF == -2 && node->left->BF == -1) node->parent->right = RightSpin(node) ; 
    else if(node->BF == -2 && node->left->BF == 1) node->parent->right = LeftRightSpin(node) ; 
    else if(node->BF == 2 && node->right->BF == -1) node->parent->right = RightLeftSpin(node) ; 
    else node->parent->right = LeftSpin(node) ; 
}
void Spin3(AVLNode *node, AVLNode **root) {
    if(node->BF == -2 && node->left->BF == -1) *root = RightSpin(node) ; 
    else if(node->BF == -2 && node->left->BF == 1) *root = LeftRightSpin(node) ; 
    else if(node->BF == 2 && node->right->BF == -1) *root = RightLeftSpin(node) ; 
    else *root = LeftSpin(node) ; 
   
}
void Judge(AVLNode *node, AVLNode **root) {
    if(!node->parent) Spin3(node, root) ; 
    else if(!(node->parent->left) || abs(node->parent->left->BF) != 2) Spin2(node) ; 
    else Spin1(node) ; 
}
void InsertUpdate(AVLNode *node, AVLNode **root) {
    if(!node) return ; 
    int LeftDeepth = GetDeepth(node->left) ; 
    int RightDeepth = GetDeepth(node->right) ; 
    int NowDeepth = max(LeftDeepth, RightDeepth) + 1 ; 
    int NowBF = RightDeepth - LeftDeepth ; 

    node->depth = NowDeepth ; 
    node->BF = NowBF ; 
    
    NowBF = abs(NowBF) ; 
    if(NowBF == 0) return ; 
    else if(NowBF == 1) InsertUpdate(node->parent, root) ;
    else {
        Judge(node, root) ; 
    }
}
AVLNode *BSTInsert(AVLNode *node, int val, AVLNode **leaf, AVLNode **root,  AVLNode *parent = nullptr) {
    if(!node) {
        *leaf = new AVLNode(val, parent) ; 
        return *leaf; 
    }

    if(val > node->data) {
        node->right = BSTInsert(node->right, val, leaf, root, node) ; 
    } else {
        node->left = BSTInsert(node->left, val, leaf, root, node) ; 
    }
    return node ; 
}
AVLNode *AVLInsert(AVLNode *node, int val, AVLNode **root) {
    AVLNode *leaf ; 
    node = BSTInsert(node, val, &leaf, root) ; 
    if(leaf->parent)InsertUpdate(leaf->parent, root) ; 
    return node ; 
}
void Show(AVLNode *root) {
    if(!root) return ; 
    cout<<root->data<<" " ;
    if(root->data == 61) cout<<root->right<<endl ; 
    Show(root->left) ; 
    Show(root->right) ; 
}
int main() {
    int n ; cin>>n ; 
    AVLNode *root = nullptr ; 
    for(int i=0 ; i<n ; i++) {
       int t ; cin>>t ;  
       root = AVLInsert(root, t, &root) ; 
    }
    Show(root) ; 
    return 0 ; 
}
