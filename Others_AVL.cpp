#include <iostream>
using namespace std;

struct node {
    int val;
    int height = 1;
    node *left = nullptr, *right = nullptr;
    node(int val) : val(val) { }
};

int getHeight(node* root)
{
    if (!root) return 0;
    return root->height;
}

void updateHeight(node* root)
{
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
}

node* L(node* root)
{
    node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

node* R(node* root)
{
    node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

int getBalanceFactor(node* root)
{
    return getHeight(root->left) - getHeight(root->right);
}

node* insert(node* root, int val)
{
    if (!root) return new node(val);
    if (val < root->val) {
        root->left = insert(root->left, val);
        updateHeight(root);
        if (getBalanceFactor(root) == 2) {
            if (getBalanceFactor(root->left) == 1) {
                root = R(root);
            } else if (getBalanceFactor(root->left) == -1) {
                root->left = L(root->left);
                root = R(root);
            }
        }
    } else if (val > root->val) {
        root->right = insert(root->right, val);
        updateHeight(root);
        if (getBalanceFactor(root) == -2) {
            if (getBalanceFactor(root->right) == -1) {
                root = L(root);
            } else if (getBalanceFactor(root->right) == 1) {
                root->right = R(root->right);
                root = L(root);
            }
        }
    }
    return root;
}

int main()
{
    int n;
    cin >> n;
    node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        root = insert(root, temp);
    }

    cout << root->val << endl;

    return 0;
}
