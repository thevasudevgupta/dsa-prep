#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

const int ABSENT_NODE_VALUE = 1e9;

class TreeNode {
    public:
        TreeNode *left;
        TreeNode *right;
        int value;

        TreeNode(int value) {
            this->value = value;
            left = right = NULL;
        }

        void print() {
            cout << value << " ";
        }
};


TreeNode *create_tree(vector<int> values) {
    TreeNode *root = NULL;

    queue<TreeNode *> q;
    int size = values.size();
    for (int i = 0; i < size; i++) {
        TreeNode *new_node = new TreeNode(values[i]);
        if (root == NULL) { root = new_node; }
        if (!q.empty()) {
            TreeNode *q_front = q.front();
            if (q_front->left == NULL) { q_front->left = new_node; }
            else if (q_front->right == NULL) { q_front->right = new_node;}

            if (q_front->left != NULL && q_front->right != NULL) { q.pop(); }
        }

        // we shouldn't add any child to the empty node
        if (new_node->value != ABSENT_NODE_VALUE) {
            q.push(new_node);
        }
    }

    // replacing all ABSENT_NODE_VALUE with NULL
    if (root != NULL) {
        queue<TreeNode *> new_q;
        new_q.push(root);
        TreeNode *tmp_ptr = NULL;
        while (!new_q.empty()) {
            TreeNode *q_front = new_q.front();

            if (q_front->left != NULL) {
                if (q_front->left->value == ABSENT_NODE_VALUE) {
                    tmp_ptr = q_front->left;
                    q_front->left = NULL;
                    delete tmp_ptr;
                }
                else { new_q.push(q_front->left); }
            }

            if (q_front->right != NULL) {
                if (q_front->right->value == ABSENT_NODE_VALUE) {
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


void preorder_push(TreeNode *root, vector<int> &values) {
    if (root == NULL) { return; }
    values.push_back(root->value);
    preorder_push(root->left, values);
    preorder_push(root->right, values);
};

vector<int> preorder_push(TreeNode *root) {
    vector<int> values;
    preorder_push(root, values);
    return values;
}


void level_wise_print(TreeNode *root) {
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


void print_pairs_with_target_sum(vector<int> values, int target) {
    bool no_pairs = true;

    unordered_map< int, list<int> > umap;
    for (int i = 0; i < values.size(); i++) {
        umap[values[i]].push_back(i);
    }

    for (int i = 0; i < values.size(); i++) {
        int diff = target - values[i];
        if (umap.find(diff) != umap.end()) {
            for (int j = 0; j < umap[diff].size(); j++) {
                cout << i << " " << umap[diff].back() << endl;
                umap[diff].pop_back();
                no_pairs = false;
            }
        }
        umap[values[i]].push_back(i);
    }

    // cout << "##########" << endl;
    // for (auto v : umap) {
    //     cout << v.first << " : ";
    //     for (int i = 0; i < v.second.size(); i++) {
    //         cout << v.second[i] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "#########" << endl;

    if (no_pairs) {
        cout << -1 << " " << -1 << endl;
    }
}

int main() {
    int target, val;
    vector<int> values;

    cin >> target;
    while (cin >> val) {
        values.push_back(val);
    }

    TreeNode *root = create_tree(values);
    // level_wise_print(root);

    vector<int> preorderd_values = preorder_push(root);
    print_pairs_with_target_sum(preorderd_values, target);

    // for (int i = 0; i < preorderd_values.size(); i++)
    //     cout << (preorderd_values[i]) << " ";
    // cout << endl;
}
