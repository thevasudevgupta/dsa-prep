#include <vector>
#include <iostream>
using namespace std;


// O(n + m) ; O(1)
vector<int> searchInSortedMatrix(vector< vector<int> > matrix, int target) {
  // Write your code here.
	int i = 0, j = matrix[0].size() - 1;
	while (i < matrix.size() && j >= 0) {
		if (matrix[i][j] == target) { return {i, j}; }
		else if (matrix[i][j] > target) { --j; }
		else { ++i; }
	}
  return {-1, -1};
}


int main() {
    vector<int> vec1(10);
    vector<int> vec2(10);
    vector< vector<int> > matrix(5);
    int target = 3;

    vec1.push_back(3); vec1.push_back(4); vec1.push_back(7);
    vec2.push_back(6); vec2.push_back(5); vec2.push_back(9);
    matrix.push_back(vec1); matrix.push_back(vec2);

    vector<int> answer = searchInSortedMatrix(matrix, target);
    for (int i = 0; i < 2; i++)
        cout << answer[i] << endl;
};
