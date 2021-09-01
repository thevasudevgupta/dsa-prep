#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(int arr1[], int arr2[], int l1, int l2) {
	int i = 0, j = 0;
	vector<int> output(l1+l2);

	while (i < l1 && j < l2) {
		if (arr1[i] < arr2[j]) {
			output.push_back(arr1[i]);
			i++;
		}
		else {
			output.push_back(arr2[j]);
			j++;
		}
	}
	
	if (i == l1 && j != l2) {
		while (j < l2) {
			output.push_back(arr2[j]);
			j++;
		}
	}
	else if (i != l1 && j == l2) {
		while (i < l1) {
			output.push_back(arr1[i]);
			i++;
		}
	}

	return output;
};

int main() {
    int arr1[] = {6, 9, 10, 11, 23};
    int arr2[] = {3, 10};

    int l1 = sizeof(arr1) / sizeof(*arr1);
    int l2 = sizeof(arr2) / sizeof(*arr2);

    cout << l1 << " " << l2 << endl;
    vector<int> output = merge(arr1, arr2, l1, l2);
    for (int i = 0; i < output.size(); i++) {
        if (i < output.size() - (l1 + l2)) { continue; }
        cout << output[i] << endl;
    }
};
