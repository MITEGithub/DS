#include <iostream>
#include <cmath>
using namespace std ; 

class AVLNode {
    public:
        int data ; 
        AVLNode *left ; 
        AVLNode *right ; 
        int depth ; 
    AVLNode(int data, int depth = 1) : data(data), depth(depth) {}
} ; 
int GetDepth(AVLNode *node) {
    if(!node) return 0 ; 
    else return node->depth ; 
}
int GetBF(AVLNode *node) {
    if(!node) return 0 ; 
    return GetDepth(node->right) - GetDepth(node->left) ; 
}
void depthupdata(AVLNode *node) {
    if(!node) return ; 
    node->depth = max(GetDepth(node->left), GetDepth(node->right)) ; 
}
AVLNode *L(AVLNode *node) {
    AVLNode *result = node->right ; 
    node->right = result->left ; 
    result->left = node ; 
    depthupdata(node) ; 
    depthupdata(result) ; 
    return result ; 
}
AVLNode *R(AVLNode *node) {
    AVLNode *result = node->left ; 
    node->left = result->right ; 
    result->right = node ; 
    depthupdata(node) ; 
    depthupdata(result) ; 
    return result ; 
}
AVLNode *Insert(AVLNode *root, int val) {
    if(!root) return new AVLNode(val) ; 
    auto *ptr = val < root->data ? root->left : root->right ; 
    auto factor = val < root->data ? 1 : -1 ; 
    auto *func_a = val < root->data ? R : L ; 
    auto *func_b = val < root->data ? L : R ; 
    
    auto func = [&root, val](auto* ptr, auto factor, auto* func_a, auto* func_b){
        root = Insert(ptr, val);
        depthupdata(root);
        if (GetBF(root) == factor * 2) {
            if (GetBF(root->left) == factor) {
                root = func_a(root);
            } else if (GetBF(root->left) == -factor) {
                ptr = func_b(ptr);
                root = func_a(root);
            }
        }
    } ; 
    func(ptr, factor, func_a, func_b) ; 
    return root ; 
} ; 
int main() {
    int n ; cin>>n ; 
    AVLNode *root ; 
    for(int i=0 ; i<n ; i++) {
        int t ; cin>>t ; 
        root = Insert(root, t) ; 
    }
    cout<<root->data ; 
    return 0 ; 
}
