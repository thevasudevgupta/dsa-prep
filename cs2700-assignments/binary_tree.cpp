// g++ -std=c++11 binary_tree.cpp && ./a.out <sample.txt

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class TreeNode {
    public:
        TreeNode *left;
        TreeNode *right;
        const char* name;
        int value;
        TreeNode(const char* name, int val);
        void print();
};

TreeNode::TreeNode(const char* name, int value) {
    this->name = name;
    this->value = value;
    left = right = NULL;
};

void TreeNode::print() {
    cout << name << "->" << value << endl;
};


class Tree {
    public:
        void create_tree(vector<const char*> names, vector<int> values);
        void preorder_print();
        void preorder_print(TreeNode *ptr);
        // void insert(char name, int value);
        Tree() {root = NULL;}
    private:
        TreeNode *root;
};

void Tree::create_tree(vector<const char*> names, vector<int> values) {
    queue<TreeNode *> q;
    for (int i = 0; i < values.size(); i++) {
        TreeNode *new_node = new TreeNode(names[i], values[i]);
        if (root == NULL) { root = new_node; }
        if (!q.empty()) {
            TreeNode *q_front = q.front();
            if (q_front->left == NULL) { q_front->left = new_node; }
            else if (q_front->right == NULL) { q_front->right = new_node;}
            
            if (q_front->left != NULL && q_front->right != NULL) { q.pop(); }
        }
        q.push(new_node);
    }
};

void Tree::preorder_print() {
    preorder_print(root);
};

void Tree::preorder_print(TreeNode *ptr) {
    if (ptr == NULL) { return; }
    ptr->print();
    preorder_print(ptr->left);
    preorder_print(ptr->right);
};


int main() {
    vector<int> values{1, 2, 3, 4, 5, 6, 7};
    vector<const char*> names{"c", "k", "m", "N", "c", "h", "c"};
    cout << endl;

    Tree tree;
    tree.create_tree(names, values);
    cout << "printing Tree" << endl;
    tree.preorder_print();
}

// int main() {
//     int T;
//     cin >> T;
//     TreeNode *root = NULL;
//     while (T--) {
//         int operation;
//         cin >> operation;
//         if (operation == 1) {
//             int n;
//             cin >> n;
//             vector<int> vals(n, -1);
//             vector<char> names;
//             for (int i = 0; i < n; i++) {
//                 char s;
//                 int v;
//                 cin >> v;
//                 cin >> s;
//                 vals[i] = v;
//                 names.push_back(s); 
//             }
//             // Tree already exists
//             if (root != NULL) {
//                // your code goes here
//             } else {
//             // your code goes here
//             }
//             cout << "doing operation-" << operation << endl;
//         }
//         if (operation == 2) {
//             char s;
//             cin >> s;
//             // your code goes here
//             cout << "doing operation-" << operation << endl;
//         }
//         if (operation == 3) {
//             char s;
//             cin >> s;
//             int count  = 0;
//             // your code goes here
//             cout << "doing operation-" << operation << endl;
//             cout << count << endl;    
//         }
//         if (operation == 4) {
//             int target;
//             cin >> target;
//             int leaf=0, non_leaf=0;
//             // your code goes here
//             cout << "doing operation-" << operation << endl;
//             cout << leaf << " " << non_leaf << endl;    
//         }
//         if (operation == 5) {
//             int target;
//             cin >> target;
//             //your code goes here
//             cout << "doing operation-" << operation << endl;
//             cout << endl;
//         }
//     }
//     return 0;
// }
