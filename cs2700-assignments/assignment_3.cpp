#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
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
}

bool compare_fn(vector<int> vec1, vector<int> vec2) {
    if (vec1[0] == vec2[0]) {
        return vec1[1] < vec2[1];
    }
    return vec1[0] < vec2[0];
}

void rearrange_and_print(vector< vector<int> > &pairs) {
    int size = pairs.size();

    for (int i = 0; i < size; i++) {
        if (pairs[i][0] > pairs[i][1]) {
            swap(pairs[i][0], pairs[i][1]);
        }
    }

    sort(pairs.begin(), pairs.end(), compare_fn);

    int l = 0, r = 0;
    for (int i = 0; i < size; i++) {
        if (l == pairs[i][0] && r == pairs[i][1]) { continue; }
        cout << pairs[i][0] << " " << pairs[i][1] << endl;
        l = pairs[i][0];
        r = pairs[i][1];
    }
}

void print_pairs_with_target_sum(vector<int> values, int target) {
    vector< vector<int> > pairs;
    int size = values.size();

    unordered_map< int, list<int> > umap;
    for (int i = 0; i < size; i++) {
        umap[values[i]].push_back(i);
    }

    for (int i = 0; i < size; i++) {
        int diff = target - values[i];
        if (umap.find(diff) != umap.end() && umap.find(values[i]) != umap.end()) {
            for (int i1 : umap[values[i]]) {
                for (int i2 : umap[diff]) {
                    vector<int> pair = {i1, i2};
                    if (i1 != i2) {
                        pairs.push_back(pair);
                    }
                }
            }
            umap.erase(diff);
            umap.erase(values[i]);
        }
    }

    if (pairs.size() == 0) {
        cout << -1 << " " << -1 << endl;
    }
    else {
        rearrange_and_print(pairs);
    }
}


int main() {
    int target, val;
    vector<int> values;

    cin >> target;
    while (cin >> val) { values.push_back(val); }

    TreeNode *root = create_tree(values);

    vector<int> preorderd_values;
    preorder_push(root, preorderd_values);

    print_pairs_with_target_sum(preorderd_values, target);
}
