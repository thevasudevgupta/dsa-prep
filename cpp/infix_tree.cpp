#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    char value;
    Node *left, *right;
    Node(char value) {
        this->value = value;
        left = right = NULL;
    }
};


bool is_opening(char bracket) {
    return bracket == '(';
}

bool is_closing(char bracket) {
    return bracket == ')';
}

Node *evaluate_infix(string input) {
    Node *node;
    int size = input.size();

    stack<Node *> stack;
    for (int i = 0; i < size; i++) {
        if (is_opening(input[i])) {
            continue;
        }
        if (is_closing(input[i])) {
            Node *t2 = stack.top(); stack.pop();
            Node *op = stack.top(); stack.pop();
            Node *t1 = stack.top(); stack.pop();
            op->left = t1; op->right = t2;
            stack.push(op);
        }
        else {
            node = new Node(input[i]);
            stack.push(node);
        }
    }

    node = stack.top(); stack.pop();
    if (!stack.empty()) { cerr << "stack is not empty!!!"; }
    return node;
}


void inorder_print(Node *root) {
    // bracket rule
    // for left sub-tree: you put bracket before processing it's child
    // for right sub-tree: you put bracket after processing it's child

    if (root == NULL) { return; }
    cout << '(';
    inorder_print(root->left);
    cout << root->value;
    inorder_print(root->right);
    cout << ')';
}


void postorder_print(Node *root) {
    if (root == NULL) { return; }
    postorder_print(root->left);
    postorder_print(root->right);
    cout << root->value;
}


int main() {
    string input = "((2*3)+(4-(5*6)))";
    Node *root = evaluate_infix(input);
    cout << "IN-ORDER: "; inorder_print(root); cout << endl;
    cout << "POST-ORDER: "; postorder_print(root); cout << endl;
}
