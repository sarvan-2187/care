#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left,*right;
    Node(int v){ data=v; left=right=NULL; }
};

int countNodes(Node* root, int l, int h) {
    if(!root) return 0;

    if(root->data < l)
        return countNodes(root->right,l,h);

    if(root->data > h)
        return countNodes(root->left,l,h);

    return 1 + countNodes(root->left,l,h) + countNodes(root->right,l,h);
}

int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(50);
    root->left->left = new Node(1);
    root->right->left = new Node(40);
    root->right->right = new Node(100);

    cout << countNodes(root,5,45);
    return 0;
}