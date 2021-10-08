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

// int apply_op(int val1, int val2, char op) {
//     if (op == '+') { return val1 + val2; }
//     else if (op == '-') { return val1 - val2; }
//     else if (op == '*') { return val1 * val2; }
//     else if (op == '/') { return val1 / val2; }
//     return -1;
// }

// int i32(char input) {
//     char zero = '0';
//     return input - zero;
// }

bool is_operator(char input) {
    return (input == '+' || input == '-' || input == '*' || input == '/');
}

Node *evaluate_postfix(string input) {
    Node *node;
    int size = input.size();

    stack<Node *> stack;
    for (int i = 0; i < size; i++) {
        node = new Node(input[i]);
        if (is_operator(input[i])) {
            Node *t2 = stack.top(); stack.pop();
            Node *t1 = stack.top(); stack.pop();
            // int value = apply_op(i32(t1->value), i32(t2->value), input[i]);
            node->left = t1; node->right = t2;
        }
        stack.push(node);
    }
    return node;
}


void postorder_print(Node *root) {
    if (root == NULL) { return; }
    postorder_print(root->left);
    postorder_print(root->right);
    cout << root->value;
}


int main() {
    string input = "123*4-+";
    Node *root = evaluate_postfix(input);
    postorder_print(root); cout << endl;
}
