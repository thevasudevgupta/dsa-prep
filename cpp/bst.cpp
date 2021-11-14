#include <iostream>
#include <vector>
using namespace std;

// THIS IS ACTUALLY THE BST CLASS
class Node {
public:
    char value;
    Node *left, *right;

    Node(char value) {
        this->value = value;
        left = right = NULL;
    }

    bool is_valid() {
        bool c1 = true, c2 = true;
        if (left != NULL) { c1 = left->value < value; }
        if (right != NULL) { c2 = right->value > value; }
        return (c1 && c2);
    }

    // void insert(int value) {
    //     Node *node = new Node(value);
    //     insert(this, node);
    // }

    void insert(Node *ptr, Node *node) {
        if (ptr->value > node->value) {
            // insert in left subtree
            cout << (ptr->left == NULL) << endl;
            if (ptr->left == NULL) {
                ptr->left = node;
                return;
            }
            else {
                insert(ptr->left, node);
            }
        }
        else if (ptr->value < node->value) {
            // insert in right subtree
            cout << (ptr->right == NULL) << endl;
            if (ptr->right == NULL) {
                ptr->right = node;
                return;
            }
            else {
                insert(ptr->right, node);
            }
        }
        else { cerr << "NOT POSSBILE TO INSERT" << endl; }
    }
};


void preorder_print(Node *root) {
    if (root == NULL) { return; }
    preorder_print(root->left);
    preorder_print(root->right);
    cout << root->value;
}

void inorder_print(Node *root) {
    if (root == NULL) { return; }
    inorder_print(root->left);
    inorder_print(root->right);
    cout << root->value;
}

void postorder_print(Node *root) {
    if (root == NULL) { return; }
    postorder_print(root->left);
    postorder_print(root->right);
    cout << root->value;
}


Node *create_tree(vector<int> input) {
    Node *root = new Node(input[0]);
    for (int i = 1; i < input.size(); i++) {
        // cout << "i " << input[i] << " ";
        Node *node = new Node(input[i]);
        root->insert(root, node);
        inorder_print(root); cout << endl;
    }
    return root;
}



int main() {
    // , 3, 4, 8, 9
    vector<int> input{1, 2};
    Node *root = create_tree(input);
    inorder_print(root); cout << endl;
    // root->insert(43); root->insert(45); root->insert(0);
    // inorder_print(root); cout << endl;
}
