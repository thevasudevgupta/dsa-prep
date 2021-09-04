#include <iostream>
using namespace std;

// O(n) ; O(1)
// though lot of computations can be done parallely
// as 2 recursive functions don't depend on each other
// so I THINK it can be done in O(log(n)) with parallel computations
int sum(int a[], int x, int y) {
        if (x > y) return 0;
        int z = (x + y) / 2;
        return a[z] + sum(a, x, z-1) + sum(a, z+1, y);
}

int main() {
    int a[] = {2, 3, 6};
    int length = sizeof(a) / sizeof(*a);
    cout << sum(a, 0, length-1) << endl;
}
