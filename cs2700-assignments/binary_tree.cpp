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
        Tree() {root = NULL;}
    private:
        TreeNode *root;
        void preorder_print(TreeNode *ptr);
        void conditional_print(TreeNode *ptr, int target);
        void search(TreeNode *ptr, char target, int *count);
        void count_conditional_leaf_nonleaf(TreeNode*, int, int*, int*);
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
    if (root == NULL) {
        cerr << "Some error in find_insert_location (inital)" << endl;
    }

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


void Tree::delete_node(char target) {
    queue<TreeNode *> q, leaves_q, parent_q;
    TreeNode *ptr;

    // cout << "passing-1" << endl;
    if ( !q.empty()) { cerr<<"P1: why q is not empty?"<<endl; }

    // saving pointers of all the leaves
    q.push(root);
    while (!q.empty()) {
        ptr = q.front()->left;
        if (ptr != NULL) {
            if (ptr->name != target && ptr->is_leaf()) {
                leaves_q.push(q.front()->left);
                parent_q.push(q.front());
            }
            else { q.push(q.front()->left); }
        }
        ptr = q.front()->right;
        if (ptr != NULL) {
            if (ptr->name != target && ptr->is_leaf()) {
                leaves_q.push(q.front()->right);
                parent_q.push(q.front());
            }
            else { q.push(q.front()->right); }
        }
        q.pop();
    }

    if ( !q.empty()) { cerr<<"P1: why q is not empty?"<<endl; }
    // cout << "passing-2" << endl;

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
                    if (leaves_q.empty()) {cout<<"here is issue-1"<<endl;}   
                    q.front()->left->name = leaves_q.front()->name;
                    q.front()->left->value = leaves_q.front()->value;
                    if (parent_q.front()->left == leaves_q.front()) {
                        parent_q.front()->left = NULL;
                    }
                    else if (parent_q.front()->right == leaves_q.front()) {
                        parent_q.front()->right = NULL;
                    }
                    else { cerr<<"buggy1"<<endl;}
                    leaves_q.pop(); parent_q.pop();
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
                    if (leaves_q.empty()) {cout<<"here is issue-2"<<endl;}
                    q.front()->right->name = leaves_q.front()->name;
                    q.front()->right->value = leaves_q.front()->value;
                    if (parent_q.front()->left == leaves_q.front()) {
                        parent_q.front()->left = NULL;
                    }
                    else if (parent_q.front()->right == leaves_q.front()) {
                        parent_q.front()->right = NULL;
                    }
                    else { cerr<<"buggy2"<<endl;}
                    leaves_q.pop(); parent_q.pop();
                    q.push(q.front()->right);
                }
            }
            else { q.push(ptr); }
        }
        q.pop();
    }

    // cout << "passing-3" << endl;
    if (!q.empty()) { cerr<<"P2: why q is not empty?"<<endl; }

    q.push(root);
    while (!q.empty()) {
        ptr = q.front()->left;
        if (ptr != NULL) {
            if (ptr->name == target) {
                if (ptr->is_leaf()) {
                    cerr << "bug1" << endl;
                }
                else {
                    cerr << "bug2" << endl;
                }
            }
            else { q.push(ptr); }
        }
        ptr = q.front()->right;
        if (ptr != NULL) {
            if (ptr->name == target) {
                if (ptr->is_leaf()) {
                    cerr << "bug3" << endl;
                }
                else {
                    cerr << "bug4" << endl;
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
            // cout << "FOR INSERTION" << endl;
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
            // cout << "################" << endl;
            // tree.level_wise_print();
            // cout << "####" << endl;
            // tree.preorder_print();
            // cout << "################" << endl;
        }
        if (operation == 2) {
            // cout << "FOR DELETION" << endl;
            char target;
            cin >> target;
            // cout << "###### BEFORE ########" << endl;
            // tree.level_wise_print();
            // cout << "################" << endl;
            tree.delete_node(target);
            // cout << "####### AFTER ########" << endl;
            // tree.level_wise_print();
            // cout << "################" << endl;
        }
        if (operation == 3) {
            // cout << "FOR SEARCH" << endl;
            char target;
            cin >> target;
            int count = tree.search(target);
            cout << count << endl;    
        }
        if (operation == 4) {
            // cout << "FOR COUNTING LEAF/NON_LEAF" << endl;
            int target;
            cin >> target;
            vector<int> count = tree.count_conditional_leaf_nonleaf(target);
            cout << count[0] << " " << count[1] << endl;    
        }
        if (operation == 5) {
            // cout << "FOR PRINT" << endl;
            int target;
            cin >> target;
            // cout << "target: " << target << endl;
            tree.conditional_print(target);
        }
    }
    return 0;
}
