// g++ -std=c++11 binary_tree.cpp && ./a.out <sample.txt

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class TreeNode {
    public:
        TreeNode *left;
        TreeNode *right;
        char name;
        int value;
        TreeNode(char name, int val);
        void print();
        bool is_leaf();
};

TreeNode::TreeNode(char name, int value) {
    this->name = name;
    this->value = value;
    left = right = NULL;
};

void TreeNode::print() {
    cout << name << "->" << value << endl;
};

bool TreeNode::is_leaf() {
    return (left == NULL && right == NULL);
}


class Tree {
    public:
        TreeNode *create_tree(vector<char> names, vector<int> values);
        void preorder_print();
        void level_wise_print();
        void conditional_print(int target);
        void insert(TreeNode *node);
        int search(char target);
        vector<int> count_conditional_leaf_nonleaf(int target);
        void delete_node(char target);
        Tree() { root = NULL; }
    private:
        TreeNode *root;
        void preorder_print(TreeNode *ptr);
        void conditional_print(TreeNode *ptr, int target);
        void search(TreeNode *ptr, char target, int *count);
        void count_conditional_leaf_nonleaf(TreeNode*, int, int*, int*);
        void insert(TreeNode *ptr, TreeNode *new_node);
};

TreeNode *Tree::create_tree(vector<char> names, vector<int> values) {
    queue<TreeNode *> q;
    int size = values.size();
    for (int i = 0; i < size; i++) {
        TreeNode *new_node = new TreeNode(names[i], values[i]);
        if (root == NULL) { root = new_node; }
        if (!q.empty()) {
            TreeNode *q_front = q.front();
            if (q_front->left == NULL) { q_front->left = new_node; }
            else if (q_front->right == NULL) { q_front->right = new_node;}

            if (q_front->left != NULL && q_front->right != NULL) { q.pop(); }
        }

        // -1 value is corresponding empy node
        // we shouldn't add any child to empty node
        if (new_node->value != -1) {
            q.push(new_node);
        }
    }

    // replacing all -1's with NULL
    if (root != NULL) {
        queue<TreeNode *> new_q;
        new_q.push(root);
        TreeNode *tmp_ptr = NULL;
        while (!new_q.empty()) {
            TreeNode *q_front = new_q.front();

            if (q_front->left != NULL) {
                if (q_front->left->value == -1) {
                    tmp_ptr = q_front->left;
                    q_front->left = NULL;
                    delete tmp_ptr;
                }
                else { new_q.push(q_front->left); }
            }

            if (q_front->right != NULL) {
                if (q_front->right->value == -1) {
                    tmp_ptr = q_front->right;
                    q_front->right = NULL;
                    delete tmp_ptr;
                }
                else { new_q.push(q_front->right); }
            }

            new_q.pop();
        }
    }
    return root;
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

void Tree::level_wise_print() {
    if (root == NULL) { return; }

    queue<TreeNode *> q;
    root->print(); q.push(root);

    while (!q.empty()) {
        TreeNode *q_front = q.front();

        if (q_front->left != NULL) {
            q_front->left->print(); q.push(q_front->left);
        }
        if (q_front->right != NULL) {
            q_front->right->print(); q.push(q_front->right);
        }
        q.pop();
    }
}

void Tree::conditional_print(TreeNode *ptr, int target) {
    if (ptr == NULL) { return; }
    if (ptr->value > target) {
        cout << ptr->name << " ";
    }
    conditional_print(ptr->left, target);
    conditional_print(ptr->right, target);
}

void Tree::conditional_print(int target) {
    conditional_print(root, target);
    cout << endl;
}

void Tree::insert(TreeNode *node) {
    if (node == NULL) { return; }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        if (q.front()->left == NULL) { q.front()->left = node; break; }
        else { q.push(q.front()->left); }

        if (q.front()->right == NULL) { q.front()->right = node; break; }
        else { q.push(q.front()->right); }
        q.pop();
    }
};

int Tree::search(char target) {
    if (root == NULL) { return 0; }
    int count = 0;
    search(root, target, &count);
    return count;
}

void Tree::search(TreeNode *ptr, char target, int *count) {
    if (ptr == NULL) { return; }
    if (target == ptr->name) { (*count)++; }
    search(ptr->left, target, count);
    search(ptr->right, target, count);
}

vector<int> Tree::count_conditional_leaf_nonleaf(int target) {
    if (root == NULL) { return {0, 0}; }
    int leaf_count = 0, non_leaf_count = 0;
    count_conditional_leaf_nonleaf(root, target, &leaf_count, &non_leaf_count);
    return {leaf_count, non_leaf_count};
}

void Tree::count_conditional_leaf_nonleaf(TreeNode *ptr, int target, int *leaf_count, int*non_leaf_count) {
    if (ptr == NULL) { return; }
    if (ptr->value == target && ptr->is_leaf()) { (*leaf_count)++; }
    else if (ptr->value == target) { (*non_leaf_count)++; }

    count_conditional_leaf_nonleaf(ptr->left, target, leaf_count, non_leaf_count);
    count_conditional_leaf_nonleaf(ptr->right, target, leaf_count, non_leaf_count);
}

TreeNode *detach_first_leaf_node(TreeNode *root, char target) {
    queue<TreeNode *> q;
    TreeNode *ptr;

    q.push(root);
    while (!q.empty()) {
        ptr = q.front()->left;
        if (ptr != NULL) {
            if (ptr->name != target && ptr->is_leaf()) {
                ptr = q.front()->left;
                // detach leaf node from tree
                q.front()->left = NULL;
                return ptr;
            }
            else { q.push(q.front()->left); }
        }
        ptr = q.front()->right;
        if (ptr != NULL) {
            if (ptr->name != target && ptr->is_leaf()) {
                ptr = q.front()->right;
                // detach leaf node from tree
                q.front()->right = NULL;
                return ptr;
            }
            else { q.push(q.front()->right); }
        }
        q.pop();
    }
    return root;
}

void Tree::delete_node(char target) {
    if (root == NULL) { return; }
    if (root->name == target) {
        if (root->is_leaf()) {
            root = NULL;
            return;
        }
        else {
            TreeNode *leaf = detach_first_leaf_node(root, target);
            root->name = leaf->name;
            root->value = leaf->value;
        }
    }

    queue<TreeNode *> q;
    TreeNode *ptr;

    q.push(root);
    while (!q.empty()) {
        ptr = q.front()->left;
        if (ptr != NULL) {
            if (ptr->name == target) {
                if (ptr->is_leaf()) {
                    q.front()->left = NULL;
                    delete ptr;
                }
                else {                 
                    TreeNode *leaf = detach_first_leaf_node(root, target);
                    q.front()->left->name = leaf->name;
                    q.front()->left->value = leaf->value;
                    q.push(q.front()->left);
                }
            }
            else { q.push(ptr); }
        }
        ptr = q.front()->right;
        if (ptr != NULL) {
            if (ptr->name == target) {
                if (ptr->is_leaf()) {
                    q.front()->right = NULL;
                    delete ptr;
                }
                else {
                    TreeNode *leaf = detach_first_leaf_node(root, target);
                    q.front()->right->name = leaf->name;
                    q.front()->right->value = leaf->value;
                    q.push(q.front()->right);
                }
            }
            else { q.push(ptr); }
        }
        q.pop();
    }
}


int main() {
    int T;
    cin >> T;
    TreeNode *root = NULL;
    Tree tree;
    while (T--) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            int n;
            cin >> n;
            vector<int> values(n, -1);
            vector<char> names;
            for (int i = 0; i < n; i++) {
                char c;
                int v;
                cin >> v;
                cin >> c;
                values[i] = v;
                names.push_back(c);
            }
            if (root != NULL) {
                Tree new_tree;
                TreeNode *new_root = new_tree.create_tree(names, values);
                tree.insert(new_root);
            } else {
                root = tree.create_tree(names, values);
            }
        }
        if (operation == 2) {
            char target;
            cin >> target;
            if (root == NULL) { continue; }
            tree.delete_node(target);
        }
        if (operation == 3) {
            char target;
            cin >> target;
            int count = tree.search(target);
            cout << count << endl;    
        }
        if (operation == 4) {
            int target;
            cin >> target;
            vector<int> count = tree.count_conditional_leaf_nonleaf(target);
            cout << count[0] << " " << count[1] << endl;    
        }
        if (operation == 5) {
            int target;
            cin >> target;
            if (root == NULL) { continue; }
            tree.conditional_print(target);
        }
    }
}
