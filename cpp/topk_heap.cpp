#include <iostream>
#include <vector>
using namespace std;

// O(N + k*log(N)), O(k)
vector<int> topK(vector<int> array, int k) {
    make_heap(array.begin(), array.end());

    vector<int> outputs;
    for (int i = 0; i < k; i++) {
        outputs.push_back(array.front());
        pop_heap(array.begin(), array.end());
        array.pop_back();
    }
    return outputs;
}


int main() {
    vector<int> elements = {23, 5, 6, 1, 3, 65, 2, 32};
    vector<int> top = topK(elements, 5);
    for (int i = 0; i < top.size(); i++) {
        cout << top[i] << " ";
    }
    cout << endl;
}
