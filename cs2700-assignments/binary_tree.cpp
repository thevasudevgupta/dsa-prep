#include <iostream>
#include <vector>
using namespace std;


class TreeNode {
    public:
        TreeNode *left;
        TreeNode *right;
        char name;
        int val;
};


int main() {
    int T;
    cin >> T;
    TreeNode *root = NULL;
    while (T--) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            int n;
            cin >> n;
            vector<int> vals(n, -1);
            vector<char> names;
            for (int i = 0; i < n; i++) {
                char s;
                int v;
                cin >> v;
                cin >> s;
                vals[i] = v;
                names.push_back(s); 
            }
            // Tree already exists
            if (root != NULL) {
               // your code goes here
            } else {
            // your code goes here
            }
        }
        if (operation==2) {
            char s;
            cin >> s;
            // your code goes here
        if (operation==3) {
            char s;
            cin >> s;
            int count  = 0;
            // your code goes here
            cout << count << endl;    
        }
        if (operation==4) {
            int target;
            cin >> target;
            int leaf=0, non_leaf=0;
            // your code goes here
            cout << leaf << " " << non_leaf << endl;    
        }
        if (operation==5) {
            int target;
            cin >> target;
            //your code goes here
            cout << endl;
        }
    }
    return 0;
}
