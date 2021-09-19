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
        void insert(TreeNode *node);
        void print();
        bool is_leaf();
};

TreeNode::TreeNode(const char* name, int value) {
    this->name = name;
    this->value = value;
    left = right = NULL;
};

void TreeNode::print() {
    cout << *name << "->" << value << endl;
};

void TreeNode::insert(TreeNode *node) {
    if (left->value == -1) { left = node; }
    else if (right->value == -1) {right = node; }
    else {std::cerr << "You can't insert here" << endl; } 
}

bool TreeNode::is_leaf() {
    return (left == NULL && right == NULL);
}

class Tree {
    public:
        TreeNode *create_tree(vector<const char*> names, vector<int> values);
        void preorder_print();
        void level_wise_print();
        void greater_preorder_print(int target);
        TreeNode *find_insert_location();
        int search(const char *target);
        Tree() {root = NULL;}
        vector<int> count_conditional_leaf_nonleaf(int);
    private:
        TreeNode *root;
        void preorder_print(TreeNode *ptr);
        void greater_preorder_print(TreeNode *ptr, int target);
        void search(TreeNode *ptr, const char *target, int *count);
        void count_conditional_leaf_nonleaf(TreeNode*, int, int*, int*);
};

TreeNode *Tree::create_tree(vector<const char*> names, vector<int> values) {
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

        // -1 value is corresponding empy node
        // we shouldn't add any child to empty node
        if (new_node->value != -1) {
            q.push(new_node);
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

void Tree::greater_preorder_print(TreeNode *ptr, int target) {
    if (ptr == NULL) { return; }
    if (ptr->value > target) {
        cout << ptr->name << " " << endl;
    }
    greater_preorder_print(ptr->left, target);
    greater_preorder_print(ptr->right, target);
}

void Tree::greater_preorder_print(int target) {
    greater_preorder_print(root, target);
    cout << endl;
}

TreeNode *Tree::find_insert_location() {
    if (root->value == -1) { cerr << "Some error in find_insert_location" << endl; }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode *q_front = q.front();

        if (q_front->left != NULL) {
            if (q_front->left->value == -1) { return q_front; }
            q.push(q_front->left);
        }
        if (q_front->right != NULL) {
            if (q_front->right->value == -1) { return q_front; }
            q.push(q_front->right);
        }
        q.pop();
    }

    cerr << "Some error in find_insert_location" << endl;
    return root;
};

int Tree::search(const char *target) {
    int *count;
    *count = 0;
    search(root, target, count);
    return *count;
}

void Tree::search(TreeNode *ptr, const char *target, int *count) {
    if (ptr == NULL) { return; }
    if (*target == *ptr->name) { (*count)++; }
    search(ptr->left, target, count);
    search(ptr->right, target, count);
}

vector<int> Tree::count_conditional_leaf_nonleaf(int target) {
    int *leaf_count, *non_leaf_count;
    *leaf_count = *non_leaf_count = 0;
    count_conditional_leaf_nonleaf(root, target, leaf_count, non_leaf_count);
    return {*leaf_count, *non_leaf_count};
}

void Tree::count_conditional_leaf_nonleaf(TreeNode *ptr, int target, int *leaf_count, int*non_leaf_count) {
    if (ptr->value == target || ptr->is_leaf()) { (*leaf_count)++; }
    else if (ptr->value == target) { (*non_leaf_count)++; }

    count_conditional_leaf_nonleaf(ptr->left, target, leaf_count, non_leaf_count);
    count_conditional_leaf_nonleaf(ptr->right, target, leaf_count, non_leaf_count);
}

// int main() {
//     vector<int> values{1, 2, 3, 4, 5, 6, 7};
//     vector<const char*> names{"c", "k", "m", "N", "c", "h", "c"};
//     cout << endl;

//     Tree tree;
//     tree.create_tree(names, values);
//     cout << "printing Tree" << endl;
//     tree.preorder_print();
// }

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
            vector<const char*> names;
            for (int i = 0; i < n; i++) {
                char c;
                int v;
                cin >> v;
                cin >> c;
                const char *s = &c;
                values[i] = v;
                names.push_back(s);
            }
            if (root != NULL) {
                cout << "hey" << endl;
                Tree new_tree; TreeNode *new_root, *insert_location;
                new_root = new_tree.create_tree(names, values);

                insert_location = tree.find_insert_location();
                if (insert_location == NULL) { cerr << "some issue here"; }
                // insert_location->print();
                insert_location->insert(new_root);
            } else {
                root = tree.create_tree(names, values);
            }
            tree.level_wise_print();
            // tree.preorder_print();
            // cout << "doing Insertion-" << operation << endl;
        }
    //     if (operation == 2) {
    //         char s;
    //         cin >> s;
    //         // your code goes here
    //         cout << "doing Deletion-" << operation << endl;
    //     }
        if (operation == 3) {
            char s;
            cin >> s;
            const char *target = &s;
            cout << "doing Searching-" << operation << endl;
            int count = tree.search(target);
            cout << count << endl;    
        }
        if (operation == 4) {
            int target;
            cin >> target;
            cout << "doing Finding-" << operation << endl;
            vector<int> count = tree.count_conditional_leaf_nonleaf(target);
            cout << count[0] << " " << count[1] << endl;    
        }
        if (operation == 5) {
            int target;
            cin >> target;
            cout << "doing printing-" << operation << endl;
            tree.greater_preorder_print(target);
            cout << endl;
        }
    }
    return 0;
}
